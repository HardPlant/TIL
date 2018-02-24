member_list.php<br>

<?php
$uid = $_POST['uid'];
$upwd = $_POST['upwd'];

$dbms_con = mysql_connect("localhost", "root", "toor");
$db_con=mysql_select_db("test",$dbms_con);

mysql_query("set name utf8");

$sql = "select * from member";
$result = mysql_query($sql,$dbms_con);

while($row = mysql_fetch_array($result)) {
    echo (
        "<table border=1>
        <tr>
        <td>$row[id]</td>
        <td>$row[pwd]</td>
        </tr>
        </table>");
}
?>