using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class Setting1ViewModel : BindableBase
    {
        #region Properties
        private bool _CAM0_Enable = true;
        public bool CAM0_Enable {
            get { return _CAM0_Enable; }
            set { SetProperty(ref _CAM0_Enable, value); }
        }

        private bool _CAM1_Enable = true;
        public bool CAM1_Enable {
            get { return _CAM1_Enable; }
            set { SetProperty(ref _CAM1_Enable, value); }
        }

        private bool _CAM2_Enable = true;
        public bool CAM2_Enable {
            get { return _CAM2_Enable; }
            set { SetProperty(ref _CAM2_Enable, value); }
        }

        private bool _CAM3_Enable = false;
        public bool CAM3_Enable {
            get { return _CAM3_Enable; }
            set { SetProperty(ref _CAM3_Enable, value); }
        }

        private UInt32 _CAM0_Position = 2000;
        public UInt32 CAM0_Position {
            get { return _CAM0_Position; }
            set { SetProperty(ref _CAM0_Position, value); }
        }

        private UInt32 _CAM1_Position = 3000;
        public UInt32 CAM1_Position {
            get { return _CAM1_Position; }
            set { SetProperty(ref _CAM1_Position, value); }
        }

        private UInt32 _CAM2_Position = 4000;
        public UInt32 CAM2_Position {
            get { return _CAM2_Position; }
            set { SetProperty(ref _CAM2_Position, value); }
        }

        private UInt32 _CAM3_Position = 5000;
        public UInt32 CAM3_Position {
            get { return _CAM3_Position; }
            set { SetProperty(ref _CAM3_Position, value); }
        }

        private UInt32 _OK_Expose = 8000;
        public UInt32 OK_Expose {
            get { return _OK_Expose; }
            set { SetProperty(ref _OK_Expose, value); }
        }

        private UInt32 _NG1_Expose = 9000;
        public UInt32 NG1_Expose {
            get { return _NG1_Expose; }
            set { SetProperty(ref _NG1_Expose, value); }
        }

        private UInt32 _NG2_Expose = 10000;
        public UInt32 NG2_Expose {
            get { return _NG2_Expose; }
            set { SetProperty(ref _NG2_Expose, value); }
        }

        private UInt32 _UNTREAT_Expose = 11000;
        public UInt32 UNTREAT_Expose {
            get { return _UNTREAT_Expose; }
            set { SetProperty(ref _UNTREAT_Expose, value); }
        }

        private UInt16 _ServoMotor_Speed = 500;
        public UInt16 ServoMotor_Speed {
            get { return _ServoMotor_Speed; }
            set { SetProperty(ref _ServoMotor_Speed, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _Send_Setting1;
        public DelegateCommand Send_Setting1 =>
            _Send_Setting1 ?? (_Send_Setting1 = new DelegateCommand(Send_Setting1_Message));
        #endregion

        #region Constructor
        public Setting1ViewModel()
        {
            
        }
        #endregion

        private void Send_Setting1_Message()
        {
            byte[] send = new byte[40];

            try
            {
                send[0] = 0xA0;
                send[1] = 0xA0;

                send[2] = CAM0_Enable ? (byte)1 : (byte)0;
                send[3] = CAM1_Enable ? (byte)1 : (byte)0;
                send[4] = CAM2_Enable ? (byte)1 : (byte)0;
                send[5] = CAM3_Enable ? (byte)1 : (byte)0;

                Array.Copy(BitConverter.GetBytes(CAM0_Position), 0, send, 6, 4);
                Array.Copy(BitConverter.GetBytes(CAM1_Position), 0, send, 10, 4);
                Array.Copy(BitConverter.GetBytes(CAM2_Position), 0, send, 14, 4);
                Array.Copy(BitConverter.GetBytes(CAM3_Position), 0, send, 18, 4);
                Array.Copy(BitConverter.GetBytes(OK_Expose), 0, send, 22, 4);
                Array.Copy(BitConverter.GetBytes(NG1_Expose), 0, send, 26, 4);
                Array.Copy(BitConverter.GetBytes(NG2_Expose), 0, send, 30, 4);
                Array.Copy(BitConverter.GetBytes(UNTREAT_Expose), 0, send, 34, 4);
                Array.Copy(BitConverter.GetBytes(ServoMotor_Speed), 0, send, 38, 2);
            }
            catch (Exception ex)
            {
                MessageBox.Show(string.Format("Exception: {0}", ex.Message.ToString()));
                return;
            }

            ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Publish(send);
        }


    }
}
