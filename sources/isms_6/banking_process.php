process.php(save info.)
<?php
$uname = $_POST['uid'];
$uacc = $_POST['upwd'];

$dbms_con = mysql_connect("localhost", "root", "toor");
$db_con=mysql_select_db("test",$dbms_con);

mysql_query("set name utf8");

//$upwd = md5($upwd);
//$upwd = hash('sha256',$upwd,true);
$upwd=hash_hmac("sha256",$upwd,"secretKey");

$sql = "insert into banking(name, account) values('$uname', '$uacc')";
$result = mysql_query($sql,$dbms_con);

if($result){
    echo "saved";
} else {
    echo "failed";
}

exit;