using System;

namespace invokee_test
{
    public class InvokeeTest
    {
        // fibonacci
        public static Int64 return_int64_arg_int64(Int64 i){
            if(i<0){
                return 0;
            }
            if(i==0 || i==1){
                return i;
            }
            return return_int64_arg_int64(i-2) + return_int64_arg_int64(i-1);
        }
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
