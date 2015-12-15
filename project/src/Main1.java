import java.util.Arrays;

public class Main1{
 String []function_etalon(float  x,String  vasya)
{
return null;
}
 String []function_main(float  x,String  vasya)
{

 System.out.println("Hello World!"); 
 return null;
}
public static void main(String[] args)
{
String  [] result;
String  [] result_etalon = new String  [2];
String  [] result_for_etalon;
float  x;
float  x_etalon;
float  x_for_etalon;
String  vasya;
String  vasya_etalon;
String  vasya_for_etalon;
boolean  isTrue;
boolean variablesCorrectByEtalon,variablesCorrect;
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
variablesCorrect = (  ((x * 100 ) - floor(x_etalon * 100 ) )  == 0 ) && ( new String(vasya).equals(vasya_etalon);
 result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);
 result = function_main(x,vasya);
isTrue = true;
variablesCorrectByEtalon = Arrays.equals(result, result) && Arrays.equals(result, result_etalon);isTrue = true;
if (Arrays.equals(result_etalon, result) && variablesCorrect && isTrue)
System.out.println(" @0@");
else
System.out.println(" @0!@");
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
variablesCorrect = (  ((x * 100 ) - floor(x_etalon * 100 ) )  == 0 ) && ( new String(vasya).equals(vasya_etalon);
 result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);
 result = function_main(x,vasya);
isTrue = true;
variablesCorrectByEtalon = false && (  ((x * 100 ) - floor(x_etalon * 100 ) )  == 0 );isTrue = true;
if (Arrays.equals(result_etalon, result) && variablesCorrect && isTrue)
System.out.println(" @1@");
else
System.out.println(" @1!@");System.gc();Runtime rt = Runtime.getRuntime();long usedMB = (rt.totalMemory() - rt.freeMemory()) / 1024 / 1024;System.out.println("memory usage" + usedMB);
}}