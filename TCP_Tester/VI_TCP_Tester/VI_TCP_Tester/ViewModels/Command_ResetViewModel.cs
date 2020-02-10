using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Windows;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class Command_ResetViewModel : BindableBase
    {
        #region Properties
        private bool _Reset_Enable = false;
        public bool Reset_Enable
        {
            get { return _Reset_Enable; }
            set { SetProperty(ref _Reset_Enable, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _Reset_Command;
        public DelegateCommand Reset_Command =>
            _Reset_Command ?? (_Reset_Command = new DelegateCommand(Clicked_Reset_Command));
        #endregion

        public Command_ResetViewModel()
        {

        }

        private void Clicked_Reset_Command()
        {
            byte[] send = new byte[40];

            send[0] = 0xD2;
            send[1] = 0xD2;
            send[2] = Reset_Enable ? (byte)1 : (byte)0;

            ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Publish(send);
        }
    }
}
