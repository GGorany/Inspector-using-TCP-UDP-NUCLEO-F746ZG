using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Windows;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class Command_ExposeViewModel : BindableBase
    {
        #region Properties
        private bool _Prohibit_Expose = false;
        public bool Prohibit_Expose
        {
            get { return _Prohibit_Expose; }
            set { SetProperty(ref _Prohibit_Expose, value); }
        }
        #endregion

        #region DelegateCommand
        private DelegateCommand _Send_Commend_Expose;
        public DelegateCommand Send_Commend_Expose =>
            _Send_Commend_Expose ?? (_Send_Commend_Expose = new DelegateCommand(Clicked_Send_Commend_Expose));
        #endregion

        public Command_ExposeViewModel()
        {

        }

        private void Clicked_Send_Commend_Expose()
        {
            byte[] send = new byte[40];

            send[0] = 0xD1;
            send[1] = 0xD1;
            send[2] = Prohibit_Expose ? (byte)1 : (byte)0;

            ApplicationService.Instance.EventAggregator.GetEvent<TCPSendEvent>().Publish(send);
        }
    }
}
