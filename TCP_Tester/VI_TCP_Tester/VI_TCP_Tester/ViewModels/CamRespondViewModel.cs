using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using VI_TCP_Tester.Models;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class CamRespondViewModel : BindableBase
    {
        #region Properties
        private byte _CAM_Number = 0;
        public byte CAM_Number {
            get { return _CAM_Number; }
            set { SetProperty(ref _CAM_Number, value); }
        }

        private UInt32 _Bolt_Number = 0;
        public UInt32 Bolt_Number {
            get { return _Bolt_Number; }
            set { SetProperty(ref _Bolt_Number, value); }
        }

        private bool _Respond_Enable = true;
        public bool Respond_Enable {
            get { return _Respond_Enable; }
            set { SetProperty(ref _Respond_Enable, value); }
        }

        private String _Result_Send = "OK";
        public String Result_Send {
            get { return _Result_Send; }
            set { SetProperty(ref _Result_Send, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _Result_NG1;
        public DelegateCommand Result_NG1 =>
            _Result_NG1 ?? (_Result_NG1 = new DelegateCommand(Clicked_NG1));

        private DelegateCommand _Result_NG2;
        public DelegateCommand Result_NG2 =>
            _Result_NG2 ?? (_Result_NG2 = new DelegateCommand(Clicked_NG2));

        private DelegateCommand _Result_NG3;
        public DelegateCommand Result_NG3 =>
            _Result_NG3 ?? (_Result_NG3 = new DelegateCommand(Clicked_NG3));

        private DelegateCommand _Result_OK;
        public DelegateCommand Result_OK =>
            _Result_OK ?? (_Result_OK = new DelegateCommand(Clicked_OK));
        #endregion

        public CamRespondViewModel()
        {
            ApplicationService.Instance.EventAggregator.GetEvent<TCPReceiveEvent>().Subscribe(TCPMessageReceive);
        }

        private void Clicked_NG1()
        {
            Result_Send = "NG1";
        }

        private void Clicked_NG2()
        {
            Result_Send = "NG2";
        }

        private void Clicked_NG3()
        {
            Result_Send = "NG3";
        }

        private void Clicked_OK()
        {
            Result_Send = "OK";
        }


        private void TCPMessageReceive(byte[] data)
        {
            if (0xC0C0 == BitConverter.ToUInt16(data, 0))
            {
                CAM_Number = data[2];
                Bolt_Number = BitConverter.ToUInt32(data, 3);

                byte[] send = new byte[8];

                try
                {
                    send[0] = 0xC1;
                    send[1] = 0xC1;
                    send[2] = CAM_Number;

                    Array.Copy(BitConverter.GetBytes(Bolt_Number), 0, send, 3, 4);

                    send[7] = CAM.Result[Result_Send];
                }
                catch (Exception ex)
                {
                    MessageBox.Show(string.Format("Exception: {0}", ex.Message.ToString()));
                    return;
                }

                if (Respond_Enable == true)
                    ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Publish(send);
            }
        }

    }
}
