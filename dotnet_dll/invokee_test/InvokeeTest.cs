using System;

namespace invokee_test
{
    public class InvokeeTest
    {
        // fibonacci
        public static Int64 return_s64_arg_s64(Int64 i){
            if(i<0){
                return 0;
            }
            if(i==0 || i==1){
                return i;
            }
            return return_s64_arg_s64(i-2) + return_s64_arg_s64(i-1);
        }
        public static Int64 ReturnInt64(Int64 i, Int64 j){
            Int64 ret = Math.Max(i, j);
            DotnetLogger($"i {i}, j {j}, ret {ret}");
            return ret;
        }
        public static double ReturnDouble(double d){
            return Math.Sqrt(d);
        }

        public static Int64 return_s64_arg_str(string str){
            Int64 ret = (Int64)str.Length;
            DotnetLogger($"return_s64_arg_str: str {str}, ret {ret.ToString()}");
            return ret;
        }

        public static string return_str_arg_str(string str){
            return return_str_arg_str_base64_dec(str);
        }
        public static string return_str_arg_str_toupper(string str){
            string ret = str.ToUpper();
            DotnetLogger($"str {str}, ret {ret}");
            return ret;
        }
        public static string return_str_arg_str_base64_dec(string str){
            byte[] bin =  Convert.FromBase64String(str);
            string ret =  BitConverter.ToString( bin ).Replace("-","");
            DotnetLogger($"return_str_arg_str_base64_dec: str {str}, ret {ret}");
            return ret;
        }
        private static void DotnetLogger(string str){
            Console.WriteLine($"[{DateTime.UtcNow}]\tDotnetLog:\t{str}");
        }
    }
}
