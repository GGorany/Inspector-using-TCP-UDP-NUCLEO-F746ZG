using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Data;
using VI_Status_Display.Models;

namespace VI_Status_Display.ViewModels
{
    public class MainWindowViewModel : BindableBase
    {
        static Dictionary<byte, string> CAMRESULT = new Dictionary<byte, string>
        {
            { 0x01, "NG1" },
            { 0x02, "NG2" },
            { 0x03, "NG3" },
            { 0x04, "OK" },
            { 0xFF, " - " }
        };

        static Dictionary<byte, string> STATES = new Dictionary<byte, string>
        {
            { 0x00, "STOP" },
            { 0x01, "RUN" },
            { 0x02, "STOPPING" },
            { 0x03, "JOG FINDING" },
            { 0x04, "JOG RUN" }
        };

        private string _title = "Visual Inspector 2 - Data Display by UDP";
        public string Title 
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        private string _ip_Address = "192.168.0.6";
        public string ip_Address 
        {
            get { return _ip_Address; }
            set { SetProperty(ref _ip_Address, value); }
        }

        private string _port = "8089";
        public string Port 
        {
            get { return _port; }
            set { SetProperty(ref _port, value); }
        }

        private bool _IsRunning;
        public bool IsRunning 
        {
            get { return _IsRunning; }
            set {
                SetProperty(ref _IsRunning, value);
                Connection.RaiseCanExecuteChanged();
                DisConnection.RaiseCanExecuteChanged();
                RaisePropertyChanged("IsNotRunning");
            }
        }

        public bool IsNotRunning { get { return !IsRunning; } }

        private String _Firmware_Version = "Not Read Yet";
        public String Firmware_Version {
            get { return _Firmware_Version; }
            set { SetProperty(ref _Firmware_Version, value); }
        }

        private UInt32 _CAM0_Trigger = 0xFFFFFFFF;
        public UInt32 CAM0_Trigger
        {
            get { return _CAM0_Trigger; }
            set { SetProperty(ref _CAM0_Trigger, value); }
        }

        private UInt32 _CAM1_Trigger = 0xFFFFFFFF;
        public UInt32 CAM1_Trigger
        {
            get { return _CAM1_Trigger; }
            set { SetProperty(ref _CAM1_Trigger, value); }
        }

        private UInt32 _CAM2_Trigger = 0xFFFFFFFF;
        public UInt32 CAM2_Trigger
        {
            get { return _CAM2_Trigger; }
            set { SetProperty(ref _CAM2_Trigger, value); }
        }

        private UInt32 _CAM3_Trigger = 0xFFFFFFFF;
        public UInt32 CAM3_Trigger
        {
            get { return _CAM3_Trigger; }
            set { SetProperty(ref _CAM3_Trigger, value); }
        }

        private UInt32 _Input_Sensing = 0xFFFFFFFF;
        public UInt32 Input_Sensing {
            get { return _Input_Sensing; }
            set { SetProperty(ref _Input_Sensing, value); }
        }

        private UInt32 _OK_Expose = 0xFFFFFFFF;
        public UInt32 OK_Expose
        {
            get { return _OK_Expose; }
            set { SetProperty(ref _OK_Expose, value); }
        }

        private UInt32 _NG1_Expose = 0xFFFFFFFF;
        public UInt32 NG1_Expose
        {
            get { return _NG1_Expose; }
            set { SetProperty(ref _NG1_Expose, value); }
        }

        private UInt32 _NG2_Expose = 0xFFFFFFFF;
        public UInt32 NG2_Expose
        {
            get { return _NG2_Expose; }
            set { SetProperty(ref _NG2_Expose, value); }
        }

        private UInt32 _Untreat_Expose = 0xFFFFFFFF;
        public UInt32 Untreat_Expose
        {
            get { return _Untreat_Expose; }
            set { SetProperty(ref _Untreat_Expose, value); }
        }

        private String _Current_State = "Not Read Yet";
        public String Current_State
        {
            get { return _Current_State; }
            set { SetProperty(ref _Current_State, value); }
        }

        private UInt32 _Encoder_Count = 0xFFFFFFFF;
        public UInt32 Encoder_Count
        {
            get { return _Encoder_Count; }
            set { SetProperty(ref _Encoder_Count, value); }
        }

        private UInt16 _Bolt_Number = 0xFFFF;
        public UInt16 Bolt_Number
        {
            get { return _Bolt_Number; }
            set { SetProperty(ref _Bolt_Number, value); }
        }


        private readonly object _lock = new object();
        private ObservableCollection<BoltInstanceData> _BoltInstanceDatas = new ObservableCollection<BoltInstanceData>();
        public ObservableCollection<BoltInstanceData> BoltInstanceDatas
        {
            get { return _BoltInstanceDatas; }
            set {
                _BoltInstanceDatas = value;
                RaisePropertyChanged("BoltInstanceDatas");
            }
        }

        #region DelegateCommand
        private DelegateCommand _CloseWindowCommand;
        public DelegateCommand CloseWindowCommand =>
            _CloseWindowCommand ?? (_CloseWindowCommand = new DelegateCommand(CloseWindow));

        private DelegateCommand _Connection;
        public DelegateCommand Connection =>
            _Connection ?? (_Connection = new DelegateCommand(Connecting, canConnecting));

        private DelegateCommand _DisConnection;
        public DelegateCommand DisConnection =>
            _DisConnection ?? (_DisConnection = new DelegateCommand(DisConnecting, canDisConnecting));
        #endregion

        private UdpClient client;
        private IPEndPoint RemoteIpEndPoint;
        private Thread t1;
        
        public MainWindowViewModel()
        {
            IsRunning = false;

            BindingOperations.EnableCollectionSynchronization(BoltInstanceDatas, _lock);
        }

    private void CloseWindow()
        {
            IsRunning = false;
        }

        private void Connecting()
        {
            try
            {
                client = new UdpClient(Int32.Parse(Port));
                RemoteIpEndPoint = new IPEndPoint(IPAddress.Parse(ip_Address), Int32.Parse(Port));

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
            client.Dispose();
            client = null;
        }

        private bool canConnecting()
        {
            if (client == null)
                return true;

            return false;
        }

        private bool canDisConnecting()
        {
            if (client == null)
                return false;

            return true;
        }

        private void Run()
        {
            try
            {
                while (IsRunning)
                {
                    UInt16 index = 0;
                    byte[] inputBytes = client.Receive(ref RemoteIpEndPoint);
                    //Debug.WriteLine("Data Received");

                    Firmware_Version = Encoding.ASCII.GetString(inputBytes, 0, 4); index += 4;
                    CAM0_Trigger = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    CAM1_Trigger = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    CAM2_Trigger = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    CAM3_Trigger = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    Input_Sensing = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    OK_Expose = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    NG1_Expose = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    NG2_Expose = BitConverter.ToUInt32(inputBytes, index); index += 4;
                    Untreat_Expose = (UInt32)BitConverter.ToUInt16(inputBytes, index); index += 4;

                    Current_State = STATES[inputBytes[index]]; index += 1;

                    Encoder_Count = BitConverter.ToUInt32(inputBytes, index); index += 4;

                    Bolt_Number = BitConverter.ToUInt16(inputBytes, index); index += 2;

                    BoltInstanceDatas.Clear();

                    for (int i = 0; i < Bolt_Number; i++)
                    {
                        UInt32 number = BitConverter.ToUInt32(inputBytes, index); index += 4;
                        UInt32 position = BitConverter.ToUInt32(inputBytes, index); index += 4;
                        string cam0, cam1, cam2, cam3;

                        if (CAMRESULT.ContainsKey(inputBytes[index]) == true)
                        { cam0 = CAMRESULT[inputBytes[index]]; index += 1; }
                        else
                            cam0 = "error";

                        if (CAMRESULT.ContainsKey(inputBytes[index]) == true)
                        { cam1 = CAMRESULT[inputBytes[index]]; index += 1; }
                        else
                            cam1 = "error";

                        if (CAMRESULT.ContainsKey(inputBytes[index]) == true)
                        { cam2 = CAMRESULT[inputBytes[index]]; index += 1; }
                        else
                            cam2 = "error";

                        if (CAMRESULT.ContainsKey(inputBytes[index]) == true)
                        { cam3 = CAMRESULT[inputBytes[index]]; index += 1; }
                        else
                            cam3 = "error";

                        BoltInstanceDatas.Add(new BoltInstanceData(number, position, cam0, cam1, cam2, cam3));
                    }

                    //RaisePropertyChanged("BoltInstanceDatas");
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
            }
        }
    }
}
