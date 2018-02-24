member_process.php(save member info.)
<?php
$uid = $_POST['uid'];
$upwd = $_POST['upwd'];

$dbms_con = mysql_connect("localhost", "root", "toor");
$db_con=mysql_select_db("test",$dbms_con);

mysql_query("set name utf8");

//$upwd = md5($upwd);
$upwd = hash('sha256',$upwd,true);

$sql = "insert into member(id, pwd) values('$uid', '$upwd')";
$result = mysql_query($sql,$dbms_con);

if($result){
    echo "saved";
    $sql = "select * from member";
    $result2 = mysql_query($sql,$dbms_con);
    echo '\n'
    echo $result2
} else {
    echo "failed";
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);
}

exit;