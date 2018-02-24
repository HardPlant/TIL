process.php(save info.)
<?php
$uname = $_POST['uid'];
$uacc = $_POST['upwd'];


# --- ENCRYPTION ---

# the key should be random binary, use scrypt, bcrypt or PBKDF2 to
# convert a string into a key
# key is specified using hexadecimal
$key = pack('H*', "bcb04b7e103a0cd8b54763051cef08bc55abe029fdebae5e1d417e2ffb2a00a3");

# show key size use either 16, 24 or 32 byte keys for AES-128, 192
# and 256 respectively
$key_size =  strlen($key);
echo "Key size: " . $key_size . "\n";

$plaintext = "This string was AES-256 / CBC / ZeroBytePadding encrypted.";

# create a random IV to use with CBC encoding
$iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_128, MCRYPT_MODE_CBC);
$iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
    
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