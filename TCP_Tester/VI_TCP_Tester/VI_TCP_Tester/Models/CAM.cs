using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace VI_TCP_Tester.Models
{
    public class CAM
    {
        static public IReadOnlyDictionary<string, byte> Result = new Dictionary<string, byte>
        {
            { "NG1" , 0x01 },
            { "NG2" , 0x02 },
            { "NG3" , 0x03 },
            { "OK" , 0x04 },
            { " - " , 0xFF }
        };
    }
}
