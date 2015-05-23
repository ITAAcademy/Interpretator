<!DOCTYPE html>
<html>
<body>

<h1>TEST PHP page</h1>

<?php
?> 
<?php /*phpinfo();*/ ?>
</body>
</html>

<?php
/*
$r = new HttpRequest('http://localhost', HttpRequest::METH_POST);
$r->setOptions(array('cookies' => array('lang' => 'en')));
$r->addPostFields(array('user' => 'mike', 'pass' => 's3c|r3t'));
//$r->addPostFile('image', 'profile.jpg', 'image/jpeg');
try {
    echo $r->send()->getBody();
} catch (HttpException $ex) {
    echo $ex;
}*/
?>

<!DOCTYPE HTML>
<html> 
<body>

<form action="http://localhost" method="post">
SesionID(none): <input type="text" name="name"><br>
Type(none): <input type="text" name="email"><br>
<br>Code: <textarea name="text" style="width: 300px; height: 400px;"> </textarea></br>
<input type="submit">
</form>

</body>
</html>