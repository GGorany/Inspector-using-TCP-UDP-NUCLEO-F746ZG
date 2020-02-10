using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Windows;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class Command_StartInspectionViewModel : BindableBase
    {
        #region Properties
        private bool _StartInspection = false;
        public bool StartInspection
        {
            get { return _StartInspection; }
            set { SetProperty(ref _StartInspection, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _Send_StartInspection;
        public DelegateCommand Send_StartInspection =>
            _Send_StartInspection ?? (_Send_StartInspection = new DelegateCommand(Clicked_Send_StartInspection));
        #endregion

        public Command_StartInspectionViewModel()
        {

        }

        private void Clicked_Send_StartInspection()
        {
            byte[] send = new byte[40];

            send[0] = 0xD0;
            send[1] = 0xD0;
            send[2] = StartInspection ? (byte)1 : (byte)0;

            ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Publish(send);
        }
    }
}
