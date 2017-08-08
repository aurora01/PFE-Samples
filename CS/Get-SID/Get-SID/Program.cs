using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Principal;


namespace Get_SID
{
    class Program
    {
        static void Main(string[] args)
        {
            // set up domain context
            var userIdentity = System.Security.Principal.WindowsIdentity.GetCurrent();
            var sid1 = userIdentity.User.Value;
            var sid2 = userIdentity.User.AccountDomainSid.Value;
            Console.WriteLine(@"SID=" + sid1);
            Console.WriteLine(@"AccountDomainSid=" + sid2);
        }
    }
}
