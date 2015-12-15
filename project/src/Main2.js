

function  function_etalon( x, vasya)
{
return 0;
}
function  function_main( x, vasya)
{

 var a="1";return a; 
 return 0;
}
var result;
var result_etalon;
var result_for_etalon;
var x;
var x_etalon;
var x_for_etalon;
var vasya;
var vasya_etalon;
var vasya_for_etalon;
var isTrue;
varvariablesCorrectByEtalon,variablesCorrect;
result_etalon[0] = "adin"
;
result_etalon[1] = "two"
;
x_for_etalon = x = 10.0
;
vasya_for_etalon = vasya = "safdasdf"
;
x_etalon = 10.0
;
vasya_etalon = "safdasdf"
;
variablesCorrect = (  ((x * 100 ) - (x_etalon * 100 ) )  == 0 ) && ( vasya == vasya_etalon );
 result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);
 result = function_main(x,vasya);
isTrue = true;
variablesCorrectByEtalon = result.toString()==result.toString() && result.toString()==result_etalon.toString();isTrue = true;
if (result_etalon.toString()==result.toString() && variablesCorrect && isTrue)
result_etalon[0] = "adin"
;
result_etalon[1] = "two"
;
x_for_etalon = x = 12.0
;
vasya_for_etalon = vasya = "safdasdf"
;
x_etalon = 12.0
;
vasya_etalon = "safdasdf"
;
variablesCorrect = (  ((x * 100 ) - (x_etalon * 100 ) )  == 0 ) && ( vasya == vasya_etalon );
 result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);
 result = function_main(x,vasya);
isTrue = true;
variablesCorrectByEtalon = false && (  ((x * 100 ) - (x_etalon * 100 ) )  == 0 );isTrue = true;
if (result_etalon.toString()==result.toString() && variablesCorrect && isTrue)
