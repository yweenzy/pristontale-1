<?php
//funчуo anti injection_SQL

function anti_sql($expressao){

  $inject = 0;
  $expressao = strtolower($expressao);

    //arrays com palavras e caracteres invalidos
    $badword1 = array("' or 0=0 --",'" or 0=0 --',"or 0=0 --","' or 0=0 #","admin'--",'" or 0=0 #',"or 0=0 #","' or 'x'='x",'" or "x"="x',"') or ('x'='x","' or 1=1--",'" or 1=1--',"or 1=1--","' or a=a--",'" or "a"="a',"') or ('a'='a",'") or ("a"="a','hi" or "a"="a','hi" or 1=1 --',"hi' or 1=1 --","hi' or 'a'='a","hi') or ('a'='a",'hi") or ("a"="a',"or '1=1'");
    $badword2 = array("select", " select","select "," insert"," update","update "," delete","delete "," drop","drop "," destroy","destroy ");

    for($i = 0; $i < sizeof($badword1); $i++){
        if(substr_count($expressao,$badword1[$i]) != 0)
          $inject = 1;
       }

         for($i = 0; $i < sizeof($badword2); $i++){
              if(substr_count($expressao,$badword2[$i]) != 0)
              $inject = 1;
   }
    $charvalidos = "abcdefghijklmnopqrstuvwxyz0123456789СРУТЧЩШЪЭЬгвдекймбсрутчщшъэьѓђєѕњљќё!?@#$%&(){}[]:;,.-_ ";

     for($i = 0; $i < strlen($expressao); $i++){
        $char = substr($expressao,$i,1);
            if(substr_count($charvalidos,$char) == 0)
               $inject = 1;
         }
    return($inject);
}
?>