using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Text;

namespace VI_Status_Display.Models
{
    public class BoltInstanceData : BindableBase
    {
        private UInt32 _Number;
        public UInt32 Number 
        {
            get { return _Number; }
            set {
                _Number = value;
                //RaisePropertyChanged("Number");
            }
        }

        private UInt32 _Position;
        public UInt32 Position 
        {
            get { return _Position; }
            set {
                _Position = value;
                //RaisePropertyChanged("Position");
            }
        }

        private string _CAM0;
        public string CAM0 
        {
            get { return _CAM0; }
            set {
                _CAM0 = value;
                //RaisePropertyChanged("CAM0");
            }
        }

        private string _CAM1;
        public string CAM1 
        {
            get { return _CAM1; }
            set {
                _CAM1 = value;
                //RaisePropertyChanged("CAM1");
            }
        }

        private string _CAM2;
        public string CAM2 
        {
            get { return _CAM2; }
            set {
                _CAM2 = value;
                //RaisePropertyChanged("CAM2");
            }
        }

        private string _CAM3;
        public string CAM3 
        {
            get { return _CAM3; }
            set {
                _CAM3 = value;
                //RaisePropertyChanged("CAM3");
            }
        }

        public BoltInstanceData(UInt32 number, UInt32 position, string cam0, string cam1, string cam2, string cam3)
        {
            this.Number = number;
            this.Position = position;
            this.CAM0 = cam0;
            this.CAM1 = cam1;
            this.CAM2 = cam2;
            this.CAM3 = cam3;
        }
    }
}
