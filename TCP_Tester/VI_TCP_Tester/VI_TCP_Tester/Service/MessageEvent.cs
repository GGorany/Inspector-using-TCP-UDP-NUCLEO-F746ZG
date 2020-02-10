using Prism.Events;
using System;
using System.Collections.Generic;
using System.Text;

namespace VI_TCP_Tester.Service
{
    public class GenericMessageEvent : PubSubEvent<string>
    {
    }

    public class TCPSendEvent : PubSubEvent<byte[]>
    {
    }

    public class TCPReceiveEvent : PubSubEvent<byte[]>
    {
    }
}
