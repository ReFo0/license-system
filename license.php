<?php
try {
        $db = new PDO("mysql:host=localhost;dbname=lisansdata;charset=utf8mb4", "username", "password");
} catch (PDOException $e) {
    print $e->getMessage();
}

if(isset($_GET["license"])){
    $license = $_GET["license"];
    if(isset($_GET["hwid"])){
        $hwid = $_GET["hwid"];
        $query = $db->query("SELECT * FROM licenses WHERE lisans_anahtar = '{$license}'")->fetch(PDO::FETCH_ASSOC);
        if($query){
            if($query["lisans_anahtar"] == $license){
                if($query["hwid"] == ""){
                    $update = $db->prepare("UPDATE licenses SET hwid=:hwid WHERE lisans_anahtar='{$license}'");
                    $save = $update->execute([
                        "hwid" => $hwid
                    ]);
                    if ($save) {
                        echo generateHash($hwid);
                    } else {
                        echo "                 ";
                    }
                }else{
                    echo generateHash($hwid);
                }
            }else{
                echo "     ";
            }
        }
    }
}

function generateHash($hwid)
{
    $date = new DateTime();
    $time = $date->getTimestamp();
    $timestr = substr($time, 0, -3);
    return md5(md5($hwid . $timestr . $hwid));
}
