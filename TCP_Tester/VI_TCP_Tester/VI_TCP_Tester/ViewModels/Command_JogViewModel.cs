using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class Command_JogViewModel : BindableBase
    {
        #region Properties
        private UInt32 _JogPosition = 0;
        public UInt32 JogPosition
        {
            get { return _JogPosition; }
            set { SetProperty(ref _JogPosition, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _Jog_Start;
        public DelegateCommand Jog_Start =>
            _Jog_Start ?? (_Jog_Start = new DelegateCommand(Clicked_Jog_Start));

        private DelegateCommand _Jog_Stop;
        public DelegateCommand Jog_Stop =>
            _Jog_Stop ?? (_Jog_Stop = new DelegateCommand(Clicked_Jog_Stop));

        private DelegateCommand _SetJogPosition;
        public DelegateCommand SetJogPosition =>
            _SetJogPosition ?? (_SetJogPosition = new DelegateCommand(Clicked_SetJogPosition));
        #endregion

        public Command_JogViewModel()
        {
            ;
        }

        private void Clicked_Jog_Start()
        {
            byte[] send = new byte[3];

            send[0] = 0xD3;
            send[1] = 0xD3;
            send[2] = 1;

            ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Publish(send);
        }

        private void Clicked_Jog_Stop()
        {
            byte[] send = new byte[3];

            send[0] = 0xD3;
            send[1] = 0xD3;
            send[2] = 0;

            ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Publish(send);
        }

        private void Clicked_SetJogPosition()
        {
            byte[] send = new byte[7];

            try
            {
                send[0] = 0xD4;
                send[1] = 0xD4;

                Array.Copy(BitConverter.GetBytes(JogPosition), 0, send, 2, 4);
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
