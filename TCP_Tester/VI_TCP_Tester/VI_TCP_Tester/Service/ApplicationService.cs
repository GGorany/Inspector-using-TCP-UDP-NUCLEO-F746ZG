using Prism.Events;
using System;
using System.Collections.Generic;
using System.Text;

namespace VI_TCP_Tester.Service
{
    public sealed class ApplicationService
    {
        private ApplicationService() { }

        private static readonly ApplicationService _instance = new ApplicationService();

        public static ApplicationService Instance { get { return _instance; } }

        private IEventAggregator _eventAggregator;
        public IEventAggregator EventAggregator {
            get {
                if (_eventAggregator == null)
                    _eventAggregator = new EventAggregator();

                return _eventAggregator;
            }
        }
    }
}
