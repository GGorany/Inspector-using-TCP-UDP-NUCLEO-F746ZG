using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Text;
using VI_TCP_Tester.Service;

namespace VI_TCP_Tester.ViewModels
{
    public class CamRequestViewModel : BindableBase
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
        #endregion

        public CamRequestViewModel()
        {
            ApplicationService.Instance.EventAggregator.GetEvent<TCPReceiveEvent>().Subscribe(TCPMessageReceive);
        }

        private void TCPMessageReceive(byte[] data)
        {
            if (0xC0C0 == BitConverter.ToUInt16(data, 0))
            {
                CAM_Number = data[2];
                Bolt_Number = BitConverter.ToUInt32(data, 3);
            }
        }
    }
}
