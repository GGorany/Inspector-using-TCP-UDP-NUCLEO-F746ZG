using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class MainWindowViewModel : BindableBase
    {
        #region Properties
        private string _title = "Visual Inspector 2 - TCP Client Tester";
        public string Title
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        private string _StatusText = "Status Text";
        public string StatusText {
            get { return _StatusText; }
            set { SetProperty(ref _StatusText, value); }
        }

        private string _ip_Address = "192.168.0.251";
        public string ip_Address {
            get { return _ip_Address; }
            set { SetProperty(ref _ip_Address, value); }
        }

        private string _port = "8082";
        public string Port {
            get { return _port; }
            set { SetProperty(ref _port, value); }
        }

        private bool _IsRunning;
        public bool IsRunning {
            get { return _IsRunning; }
            set {
                SetProperty(ref _IsRunning, value);
                Connection.RaiseCanExecuteChanged();
                DisConnection.RaiseCanExecuteChanged();
                RaisePropertyChanged("IsNotRunning");
            }
        }

        public bool IsNotRunning { get { return !IsRunning; } }

        private string _DebugMessage = "None";
        public string DebugMessage
        {
            get { return _DebugMessage; }
            set { SetProperty(ref _DebugMessage, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _CloseWindowCommand;
        public DelegateCommand CloseWindowCommand =>
            _CloseWindowCommand ?? (_CloseWindowCommand = new DelegateCommand(DisConnecting));

        private DelegateCommand _Connection;
        public DelegateCommand Connection =>
            _Connection ?? (_Connection = new DelegateCommand(Connecting, canConnecting));

        private DelegateCommand _DisConnection;
        public DelegateCommand DisConnection =>
            _DisConnection ?? (_DisConnection = new DelegateCommand(DisConnecting, canDisConnecting));
        #endregion

        private TcpClient client;
        private NetworkStream stream;
        private Thread t1;

        public MainWindowViewModel()
        {
            IsRunning = false;
            ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Subscribe(TCPMessageSend);
            ApplicationService.Instance.EventAggregator.GetEvent<TCPReceiveEvent>().Subscribe(TCPMessageReceive);
        }

        private void Connecting()
        {
            try
            {
                t1 = new Thread(Run);
                IsRunning = true;
                t1.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
        }

        private void DisConnecting()
        {
            IsRunning = false;
            if (client != null)
                client.Close();
        }

        private bool canConnecting()
        {
            if (IsRunning == false)
                return true;

            return false;
        }

        private bool canDisConnecting()
        {
            if (IsRunning == false)
                return false;

            return true;
        }

        private void Run()
        {
            try
            {
                byte[] outbuf = new byte[256];
                StatusText = "Start Connection...";

                client = new TcpClient(ip_Address, Int32.Parse(Port));
                stream = client.GetStream();

                StatusText = "Connection.";

                while (IsRunning)
                {
                    int nbytes = stream.Read(outbuf, 0, outbuf.Length);

                    ApplicationService.Instance.EventAggregator.GetEvent<TCPReceiveEvent>().Publish(outbuf);

                    for (int i = 0; i < 256; i++)
                        outbuf[i] = 0;

                    //Thread.Sleep(1);

                }  // end of outer while
            }
            catch (SocketException se)
            {
                MessageBox.Show(string.Format("SocketException: {0}", se.Message.ToString()));
            }
            catch (Exception ex)
            {
                MessageBox.Show(string.Format("Exception: {0}", ex.Message.ToString()));
            }
            finally
            {
                // Stop listening for new clients.
                if (client != null)
                    client.Close();
                StatusText = "TCP Client Closed.";
            }
        }


        private void TCPMessageSend(byte[] data)
        {
            if ((IsRunning != true) || (stream == null))
                return;

            try
            {
                stream.Write(data, 0, data.Length);
            }
            catch (Exception ex)
            {
                MessageBox.Show(string.Format("Exception: {0}", ex.Message.ToString()));
            }
        }

        private void TCPMessageReceive(byte[] data)
        {
            byte[] tmp = new byte[256];

            if (0xE0E0 == BitConverter.ToUInt16(data, 0))
            {
                Array.Copy(data, 2, tmp, 0, data.Length - 2);
                DebugMessage = Encoding.UTF8.GetString(tmp);
            }
        }
    }
}
