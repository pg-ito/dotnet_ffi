using System;

namespace invokee_test
{
    public class InvokeeTest
    {
        public static Int64 ReturnInt64(Int64 i, Int64 j){
            Int64 ret = Math.Max(i, j);
            Console.WriteLine($"i {i}, j {j}, ret {ret}");
            return ret;
        }
        public static double ReturnDouble(double d){
            return Math.Sqrt(d);
        }
        public static string ReturnString(string str){
            string ret = str.ToUpper();
            Console.WriteLine($"str {str}, ret {ret}");
            return ret;
        }
    }
}
