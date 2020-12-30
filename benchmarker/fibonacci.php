<?php

function fibo_php($i){
	if($i<0){
		return 0;
	}
	if($i==0 || $i==1){
		return $i;
	}
	return fibo_php($i-2) + fibo_php($i-1);
}