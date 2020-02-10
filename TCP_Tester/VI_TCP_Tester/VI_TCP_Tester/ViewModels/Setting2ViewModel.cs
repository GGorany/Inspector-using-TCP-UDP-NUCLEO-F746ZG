using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class Setting2ViewModel : BindableBase
    {
        #region Properties
        private UInt16 _CAM_RESULT_Waiting_Time = 1000;
        public UInt16 CAM_RESULT_Waiting_Time {
            get { return _CAM_RESULT_Waiting_Time; }
            set { SetProperty(ref _CAM_RESULT_Waiting_Time, value); }
        }

        private UInt16 _OK_Expose_Time = 100;
        public UInt16 OK_Expose_Time {
            get { return _OK_Expose_Time; }
            set { SetProperty(ref _OK_Expose_Time, value); }
        }

        private UInt16 _NG1_Expose_Time = 100;
        public UInt16 NG1_Expose_Time {
            get { return _NG1_Expose_Time; }
            set { SetProperty(ref _NG1_Expose_Time, value); }
        }

        private UInt16 _NG2_Expose_Time = 100;
        public UInt16 NG2_Expose_Time {
            get { return _NG2_Expose_Time; }
            set { SetProperty(ref _NG2_Expose_Time, value); }
        }

        private UInt16 _UNTREAT_Expose_Time = 100;
        public UInt16 UNTREAT_Expose_Time {
            get { return _UNTREAT_Expose_Time; }
            set { SetProperty(ref _UNTREAT_Expose_Time, value); }
        }

        private UInt16 _STOP_After_Delay_Time = 2000;
        public UInt16 STOP_After_Delay_Time {
            get { return _STOP_After_Delay_Time; }
            set { SetProperty(ref _STOP_After_Delay_Time, value); }
        }

        private UInt16 _START_After_Delay_Time = 1500;
        public UInt16 START_After_Delay_Time {
            get { return _START_After_Delay_Time; }
            set { SetProperty(ref _START_After_Delay_Time, value); }
        }

        private UInt16 _Supply_Delay_Time = 8763;
        public UInt16 Supply_Delay_Time {
            get { return _Supply_Delay_Time; }
            set { SetProperty(ref _Supply_Delay_Time, value); }
        }

        private UInt16 _Supply_Delay_Equipment_Stop_Time = 2341;
        public UInt16 Supply_Delay_Equipment_Stop_Time {
            get { return _Supply_Delay_Equipment_Stop_Time; }
            set { SetProperty(ref _Supply_Delay_Equipment_Stop_Time, value); }
        }

        private bool _Lighting_Trigger_Enable = false;
        public bool Lighting_Trigger_Enable {
            get { return _Lighting_Trigger_Enable; }
            set { SetProperty(ref _Lighting_Trigger_Enable, value); }
        }

        private UInt32 _Lighting_Position = 1000;
        public UInt32 Lighting_Position {
            get { return _Lighting_Position; }
            set { SetProperty(ref _Lighting_Position, value); }
        }

        private UInt16 _Lighting_Time = 200;
        public UInt16 Lighting_Time {
            get { return _Lighting_Time; }
            set { SetProperty(ref _Lighting_Time, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _Send_Setting2;
        public DelegateCommand Send_Setting2 =>
            _Send_Setting2 ?? (_Send_Setting2 = new DelegateCommand(Send_Setting2_Message));
        #endregion

        #region Construct
        public Setting2ViewModel()
        {

        }
        #endregion

        private void Send_Setting2_Message()
        {
            byte[] send = new byte[27];

            try
            {
                send[0] = 0xA1;
                send[1] = 0xA1;

                Array.Copy(BitConverter.GetBytes(CAM_RESULT_Waiting_Time), 0, send, 2, 2);
                Array.Copy(BitConverter.GetBytes(OK_Expose_Time), 0, send, 4, 2);
                Array.Copy(BitConverter.GetBytes(NG1_Expose_Time), 0, send, 6, 2);
                Array.Copy(BitConverter.GetBytes(NG2_Expose_Time), 0, send, 8, 2);
                Array.Copy(BitConverter.GetBytes(UNTREAT_Expose_Time), 0, send, 10, 2);
                Array.Copy(BitConverter.GetBytes(STOP_After_Delay_Time), 0, send, 12, 2);
                Array.Copy(BitConverter.GetBytes(START_After_Delay_Time), 0, send, 14, 2);
                Array.Copy(BitConverter.GetBytes(Supply_Delay_Time), 0, send, 16, 2);
                Array.Copy(BitConverter.GetBytes(Supply_Delay_Equipment_Stop_Time), 0, send, 18, 2);

                send[20] = Lighting_Trigger_Enable ? (byte)1 : (byte)0;

                Array.Copy(BitConverter.GetBytes(Lighting_Position), 0, send, 21, 4);
                Array.Copy(BitConverter.GetBytes(Lighting_Time), 0, send, 25, 2);
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
