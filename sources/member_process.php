member_process.php(save member info.)
<?php
$uid = $_POST['uid'];
$upwd = $_POST['upwd'];

$dbms_con = mysql_connect("localhost", "root", "toor");
$db_con=mysql_select_db($sql,$dbms_con);

mysql_query("set name utf8");

$sql = "inert into member(id, pwd) values('$uid', '$upwd')";
$result = mysql_query($sql,$dbms_con);

if($result){
    echo "saved";
} else {
    echo "failed";
}

exit;