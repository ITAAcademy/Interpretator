

<?php 
function   function_main($x)
{

  
 return  "fG13791323`02y13`132/4-28*2";
}
function   function_etalon($x)
{
return 3;return  "fG13791323`02y13`132/4-28*2";
}
  $result = 1;
  $result_etalon = 1;
  $result_for_etalon = 1;
  $x = 1;
  $x_etalon = 1;
  $x_for_etalon = 1;
  $variablesCorrect = 1;
  $variablesCorrectByEtalon = 1;
$x_for_etalon = $x = 3;
 ob_start();
$result_for_etalon = function_etalon( $x_for_etalon);
 ob_end_clean();
 ob_start();
$result = function_main( $x);
 ob_end_clean();
$variablesCorrect = true;
;
$variablesCorrectByEtalon = ( $result == $result ) && gettype($result) == gettype($result);
if (( $result  == $result_for_etalon ) && gettype($result ) == gettype($result_for_etalon) && $variablesCorrect && $variablesCorrectByEtalon)
echo " @0@";
else
echo " @0!@";
?>
