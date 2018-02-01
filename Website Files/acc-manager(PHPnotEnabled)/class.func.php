<?php

class func{  function is_valid_string($string){

        $cfgBadChars = '`~!@#$%^&*()+-_=[]{};\'\\:"|,/<>?¹²³£¢¬ªº°.,§| ';

        if(empty($string))
            return true;

        for($i = 0; $i < strlen($cfgBadChars); $i++):
            if(strstr($string, $cfgBadChars[$i]))
            return true;
			
        endfor;
        
        return false;
    }

    #function filter co mot gia tri la $ojb cai ma ban se kiem tra
    
	function char_filter($ojb){
		
        $badchars='Ý`~!@$%^()+-_=[]{}\'\\:"|,/<>? '; # Nhung ky tu khong cho phep duoc len danh sach tai day
        
		for ($i=0;$i<strlen($badchars);$i++){
            
			$ojb=str_replace($badchars[$i],"",$ojb);

        }

        return $ojb;
    }

    function getInt($o)
    {
        $err = false;

        for($i=0;$i<strlen($o);$i++)
            if(!eregi("^[0-9]",$o[$i])) $err = true;

        if($err){
			
            ereg('[^0-9]*([0-9]+)[^0-9]*', $o, $cutInt);
            $o = intval($cutInt[1]);
            if(!$o)
			
                return false;

            return $o;
        }

        return $o;

    }

    function checkSkillPoints($level,$kind)
    {
        $SP = intval((($level-10) /2))+1;

        if($level >= 55) $SP = $SP + 1;
        if($level >= 70) $SP = $SP + 1;
        if($level >= 80) $SP = $SP + 2;

        $EP = intval((($level-60) /2))+1;

        return($kind == 'SP' )? $SP:$EP;
    }

    function checkStatePoints($level){
		
        $points = (($level)*5)-5;

        for($i = 80; $i <= $level; $i++){
            
			$points+=2;
        
		}
		
        for($i = 90; $i <= $level; $i++){
			
            $points+=3;
        
		}

        if($level >= 30) $points = $points+5;
        if($level >= 70) $points = $points+5;
        if($level >= 80) $points = $points+5;

        return $points;
    }

    function char2Name($classNum)
    {
        switch ($classNum)
        {
            case "01":
                $charClassName="Fighter";
            break;

            case "02":
                $charClassName="Mechanician";
            break;

            case "03":
                $charClassName="Archer";
            break;

            case "04":
                $charClassName="Pikeman";
            break;

            case "05":
                $charClassName="Atalanta";
            break;

            case "06":
                $charClassName="Knight";
            break;

            case "07":
                $charClassName="Magician";
            break;

            case "08":
                $charClassName="Priestess";
            break;

            default:
                return false;

        }

        return $className;
    }


    function char2Num($className)
    {
        switch ($className)
        {
            case "Fighter":
                $classNum=1;
            break;

            case "Mechanician":
                $classNum=2;
            break;

            case "Archer":
                $classNum=3;
            break;

            case "Pikeman":
                $classNum=4;
            break;

            case "Atalanta":
                $classNum=5;
            break;

            case "Knight":
                $classNum=6;
            break;

            case "Magician":
                $classNum=7;
            break;

            case "Priestess":
                $classNum=8;
            break;

            default:
                return false;


        }

        return $classNum;
    }


    function charResetState($class)
    {

        switch ($class)
        {
            case "Fighter":
                $charStr=pack('i', 28);
                $charSpi=pack('i', 6);
                $charTal=pack('i', 21);
                $charAgi=pack('i', 17);
                $charHea=pack('i', 27);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

            case "Mechanician":
                $charStr=pack('i', 24);
                $charSpi=pack('i', 8);
                $charTal=pack('i', 25);
                $charAgi=pack('i', 18);
                $charHea=pack('i', 24);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

            case "Archer":
                $charStr=pack('i', 17);
                $charSpi=pack('i', 11);
                $charTal=pack('i', 21);
                $charAgi=pack('i', 27);
                $charHea=pack('i', 23);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

            case "Pikeman":
                $charStr=pack('i', 26);
                $charSpi=pack('i', 9);
                $charTal=pack('i', 20);
                $charAgi=pack('i', 19);
                $charHea=pack('i', 25);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

            case "Atalanta":
                $charStr=pack('i', 23);
                $charSpi=pack('i', 15);
                $charTal=pack('i', 19);
                $charAgi=pack('i', 19);
                $charHea=pack('i', 23);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

            case "Knight":
                $charStr=pack('i', 26);
                $charSpi=pack('i', 13);
                $charTal=pack('i', 17);
                $charAgi=pack('i', 19);
                $charHea=pack('i', 24);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

            case "Magician":
                $charStr=pack('i', 16);
                $charSpi=pack('i', 29);
                $charTal=pack('i', 19);
                $charAgi=pack('i', 14);
                $charHea=pack('i', 21);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

            case "Priestess":
                $charStr=pack('i', 15);
                $charSpi=pack('i', 28);
                $charTal=pack('i', 21);
                $charAgi=pack('i', 15);
                $charHea=pack('i', 20);
                $charStateStr=$charStr . $charSpi . $charTal . $charAgi . $charHea;
            break;

        }

        return $charStateStr;


    }

    function charResetHair($class,$model)
    {
        switch ($class)
        {
            case "Fighter":
                $modelName1=pack("a*","char\\tmABCD\\b001.ini").pack("h*",00);
                $modelName2=pack("a*","char\\tmABCD\\tmh-b02.inf").pack("h*",00);
            break;

            case "Mechanician":
                $modelName1=pack("a*","char\\tmABCD\\a001.ini").pack("h*",00);
                $modelName2=pack("a*","char\\tmABCD\\tmh-a02.inf").pack("h*",00);
            break;

            case "Archer":
                $modelName1=pack("a*","char\\tmABCD\\d001.ini").pack("h*",00);
                $modelName2=pack("a*","char\\tmABCD\\tfh-D01.inf").pack("h*",00);
            break;

            case "Pikeman":
                $modelName1=pack("a*","char\\tmABCD\\c001.ini").pack("h*",00);
                $modelName2=pack("a*","char\\tmABCD\\tmh-c02.inf").pack("h*",00);
            break;

            case "Atalanta":
                $modelName1=pack("a*","char\\tmABCD\\mb001.ini");
                $modelName2=pack("a*","char\\tmABCD\\Mfh-B02.inf").pack("h*",00);
            break;

            case "Knight":
                $modelName1=pack("a*","char\\tmABCD\\ma001.ini");
                $modelName2=pack("a*","char\\tmABCD\\Mmh-A03.inf").pack("h*",00);
            break;

            case "Magician":
                $modelName1=pack("a*","char\\tmABCD\\md001.ini");
                $modelName2=pack("a*","char\\tmABCD\\Mmh-D01.inf").pack("h*",00);
            break;

            case "Priestess":
                $modelName1=pack("a*","char\\tmABCD\\mc001.ini");
                $modelName2=pack("a*","char\\tmABCD\\Mfh-C01.inf").pack("h*",00);
            break;
        }

        $model=($model==1)?$modelName1:$modelName2;

        return $model;
    }

    function charResetSkill()
    {
        $tier0_1=pack("h*",00);
        $tier0_2=pack("h*",00);
        $tier0_3=pack("h*",00);
        $tier0_4=pack("h*",00);

        $tier1_1=pack("h*",00);
        $tier1_2=pack("h*",00);
        $tier1_3=pack("h*",00);
        $tier1_4=pack("h*",00);

        $tier2_1=pack("h*",00);
        $tier2_2=pack("h*",00);
        $tier2_3=pack("h*",00);
        $tier2_4=pack("h*",00);

        $tier3_1=pack("h*",00);
        $tier3_2=pack("h*",00);
        $tier3_3=pack("h*",00);
        $tier3_4=pack("h*",00);

        $skillStr=$tier3_4.$tier0_1.$tier0_2.$tier0_3.$tier0_4.
            $tier1_1.$tier1_2.$tier1_3.$tier1_4.
            $tier2_1.$tier2_2.$tier2_3.$tier2_4.
            $tier3_1.$tier3_2.$tier3_3;

        return $skillStr;
    }

    function charResetMastery()
    {
        $tier0_1=trim(pack("i",5000));
        $tier0_2=trim(pack("i",5000));
        $tier0_3=trim(pack("i",5000));
        $tier0_4=trim(pack("i",5000));

        $tier1_1=trim(pack("i",5000));
        $tier1_2=trim(pack("i",5000));
        $tier1_3=trim(pack("i",5000));
        $tier1_4=trim(pack("i",5000));

        $tier2_1=trim(pack("i",5000));
        $tier2_2=trim(pack("i",5000));
        $tier2_3=trim(pack("i",5000));
        $tier2_4=trim(pack("i",5000));

        $tier3_1=trim(pack("i",5000));
        $tier3_2=trim(pack("i",5000));
        $tier3_3=trim(pack("i",5000));
        $tier3_4=trim(pack("i",5000));

        $masteryStr=$tier3_4.$tier0_1.$tier0_2.$tier0_3.$tier0_4.
            $tier1_1.$tier1_2.$tier1_3.$tier1_4.
            $tier2_1.$tier2_2.$tier2_3.$tier2_4.
            $tier3_1.$tier3_2.$tier3_3;

        return $masteryStr;
    }

    function charFullMastery()
    {
        $tier0_1=trim(pack("i",10000));
        $tier0_2=trim(pack("i",10000));
        $tier0_3=trim(pack("i",10000));
        $tier0_4=trim(pack("i",10000));

        $tier1_1=trim(pack("i",10000));
        $tier1_2=trim(pack("i",10000));
        $tier1_3=trim(pack("i",10000));
        $tier1_4=trim(pack("i",10000));

        $tier2_1=trim(pack("i",10000));
        $tier2_2=trim(pack("i",10000));
        $tier2_3=trim(pack("i",10000));
        $tier2_4=trim(pack("i",10000));

        $tier3_1=trim(pack("i",10000));
        $tier3_2=trim(pack("i",10000));
        $tier3_3=trim(pack("i",10000));
        $tier3_4=trim(pack("i",10000));

        $masteryStr=$tier3_4.$tier0_1.$tier0_2.$tier0_3.$tier0_4.
            $tier1_1.$tier1_2.$tier1_3.$tier1_4.
            $tier2_1.$tier2_2.$tier2_3.$tier2_4.
            $tier3_1.$tier3_2.$tier3_3;

        return $masteryStr;
    }

    function numDir($name)
    {
        $character=array
        (
            "0"=>"48",
            "1"=>"49",
            "2"=>"50",
            "3"=>"51",
            "4"=>"52",
            "5"=>"53",
            "6"=>"54",
            "7"=>"55",
            "8"=>"56",
            "9"=>"57",

            "a"=>"65",
            "b"=>"66",
            "c"=>"67",
            "d"=>"68",
            "e"=>"69",
            "f"=>"70",
            "g"=>"71",
            "h"=>"72",
            "i"=>"73",
            "j"=>"74",
            "k"=>"75",
            "l"=>"76",
            "m"=>"77",
            "n"=>"78",
            "o"=>"79",
            "p"=>"80",
            "q"=>"81",
            "r"=>"82",
            "s"=>"83",
            "t"=>"84",
            "u"=>"85",
            "v"=>"86",
            "w"=>"87",
            "x"=>"88",
            "y"=>"89",
            "z"=>"90",

            "A"=>"65",
            "B"=>"66",
            "C"=>"67",
            "D"=>"68",
            "E"=>"69",
            "F"=>"70",
            "G"=>"71",
            "H"=>"72",
            "I"=>"73",
            "J"=>"74",
            "K"=>"75",
            "L"=>"76",
            "M"=>"77",
            "N"=>"78",
            "O"=>"79",
            "P"=>"80",
            "Q"=>"81",
            "R"=>"82",
            "S"=>"83",
            "T"=>"84",
            "U"=>"85",
            "V"=>"86",
            "W"=>"87",
            "X"=>"88",
            "Y"=>"89",
            "Z"=>"90",
        );

        for($i=0;$i<strlen($name);$i++)
        {
            $total+=$character[$name[$i]];
            if($total>=256)
                $total=$total-256;
        }

        return $total;
    }
}

//função anti injection_SQL

function filtro($expressao){

  $inject = 0;
  $expressao = strtolower($expressao);

    //arrays com palavras e caracteres invalidos
    $badword1 = array("' or 0=0 --",'" or 0=0 --',"or 0=0 --","' or 0=0 #","admin'--",'" or 0=0 #',"or 0=0 #","' or 'x'='x",'" or "x"="x',"') or ('x'='x","' or 1=1--",'" or 1=1--',"or 1=1--","' or a=a--",'" or "a"="a',"') or ('a'='a",'") or ("a"="a','hi" or "a"="a','hi" or 1=1 --',"hi' or 1=1 --","hi' or 'a'='a","hi') or ('a'='a",'hi") or ("a"="a',"or '1=1'");
    $badword2 = array("select", " select","select "," insert"," update","update "," delete","delete "," drop","drop "," destroy","destroy ");

    for($i = 0;$i < sizeof($badword1);$i++) {
        if(substr_count($expressao,$badword1[$i])!=0)
          $inject=1;
       }

         for($i=0;$i<sizeof($badword2);$i++)    {
              if(substr_count($expressao,$badword2[$i])!=0)
              $inject=1;
   }
    $charvalidos = "abcdefghijklmnopqrstuvwxyz0123456789ÁÀÃÂÇÉÈÊÍÌÓÒÔÕÚÙÜÑáàãâçéèêíìóòôõúùüñ!?@#$%&(){}[]:;,.-_/ ";

     for($i=0;$i<strlen($expressao);$i++)    {
        $char = substr($expressao,$i,1);
            if(substr_count($charvalidos,$char)==0)
               $inject=1;
         }
    return($inject);
}


//FUNÇÃO QUE MUDA A IMAGEM NOVA DO CHAR CORPO INTEIRO
	function CharImg($charClasse){
		
		if($charClasse == "Fighter"){ $charClasse = '<img src="img/classes/lutador.png"/>'; }
   else if($charClasse == "Mechanician"){ $charClasse = '<img src="img/classes/mecanico.png"/>'; }
   else if($charClasse == "Archer"){ $charClasse = '<img src="img/classes/arqueira.png"/>'; }
   else if($charClasse == "Magician"){ $charClasse = '<img src="img/classes/mago.png"/>'; }
   else if($charClasse == "Atalanta"){ $charClasse = '<img src="img/classes/atalanta.png"/>'; }
   else if($charClasse == "Knight"){ $charClasse = '<img src="img/classes/cavaleiro.png"/>'; }
   else if($charClasse == "Priestess"){ $charClasse = '<img src="img/classes/sacerdotiza.png"/>'; }
   else if($charClasse == "Pikeman"){ $charClasse = '<img src="img/classes/pike.png"/>'; }
		
		return $charClasse;
	}
	
//FUNÇÃO QUE MUDA A IMAGEM NOVA DO CHAR CORPO INTEIRO PELO NUMERO
	function CharImgInv($charClasse){
		
		if($charClasse == 1){ $charClasse = '<img src="img/classes/lutador.png"/>'; }
   else if($charClasse == 2){ $charClasse = '<img src="img/classes/mecanico.png"/>'; }
   else if($charClasse == 3){ $charClasse = '<img src="img/classes/arqueira.png"/>'; }
   else if($charClasse == 7){ $charClasse = '<img src="img/classes/mago.png"/>'; }
   else if($charClasse == 5){ $charClasse = '<img src="img/classes/atalanta.png"/>'; }
   else if($charClasse == 6){ $charClasse = '<img src="img/classes/cavaleiro.png"/>'; }
   else if($charClasse == 8){ $charClasse = '<img src="img/classes/sacerdotiza.png"/>'; }
   else if($charClasse == 4){ $charClasse = '<img src="img/classes/pike.png"/>'; }
   else { $charClasse = '<img src="img/classes/none.png"/>'; }
		
		return $charClasse;
	}


//VERIFICA SE A VARIVEL ESTÁ VAZIO E RETORNA MENSAGEM
	function VarEmpty($var){
		
		if(empty($var)){ $var = 'Information not updated.'; }
   else if(!empty($var)){ $var = $var; }
		
		return $var;
	}

//ACHA A PASTA DA ID CONVIDADA
function subDiretorio($pasta)
{
 	$total = 0;
	for($i = 0; $i < strlen($pasta); $i++){
					
		$total += ord(strtoupper($pasta[$i]));
			
			if($total >= 256){ $total = $total - 256; }
		
	}
	
	return $total;
}


//FUNÇÃO QUE MUDA A IMAGEM NOVA DO CHAR CORPO INTEIRO
	function CharImgMini($charClasse){
		
		if($charClasse == 1){ $charClasse = '<img src="img/classes/lutador.fw.png"/>'; }
   else if($charClasse == 2){ $charClasse = '<img src="img/classes/mecanico.fw.png"/>'; }
   else if($charClasse == 3){ $charClasse = '<img src="img/classes/arqueira.fw.png"/>'; }
   else if($charClasse == 7){ $charClasse = '<img src="img/classes/mago.fw.png"/>'; }
   else if($charClasse == 5){ $charClasse = '<img src="img/classes/atalanta.fw.png"/>'; }
   else if($charClasse == 6){ $charClasse = '<img src="img/classes/cavaleiro.fw.png"/>'; }
   else if($charClasse == 8){ $charClasse = '<img src="img/classes/sacerdotiza.fw.png"/>'; }
   else if($charClasse == 4){ $charClasse = '<img src="img/classes/pike.fw.png"/>'; }
		
		return $charClasse;
	}

//FUNÇÃO QUE MUDA NOME DO CHAR PT-BR OU EN-EUA
	function charName($charClasse){
		
		if($charClasse == "Fighter"){ $charClasse = 'Fighter'; }
   else if($charClasse == "Mechanician"){ $charClasse = 'Mechanician'; }
   else if($charClasse == "Archer"){ $charClasse = 'Archer'; }
   else if($charClasse == "Magician"){ $charClasse = 'Magician'; }
   else if($charClasse == "Atalanta"){ $charClasse = 'Atalanta'; }
   else if($charClasse == "Knight"){ $charClasse = 'Knight'; }
   else if($charClasse == "Priestess"){ $charClasse = 'Priestess'; }
   else if($charClasse == "Pikeman"){ $charClasse = 'Pikeman'; }
		
		return $charClasse;
	}


?>
