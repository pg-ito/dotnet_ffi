﻿using System;

namespace invokee_test
{
    public class InvokeeTest
    {
        public static Int64 ReturnInt64(Int64 i, Int64 j){
            return Math.Max(i, j);
        }
        public static double ReturnDouble(double d){
            return Math.Sqrt(d);
        }
        public static string ReturnString(string str){
            return str.ToUpper();
        }
    }
}
