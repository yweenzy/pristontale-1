<?php
/**
 * HTML_Crypt provides methods to encrypt text, which
 * can be later be decrypted using JavaScript on the client side
 *
 * PHP version 4 and 5
 *
 * @category HTML
 * @package  HTML_Crypt
 * @author   Michael Dransfield <mike@blueroot.net>
 * @license  http://www.php.net/license  PHP License
 * @version  CVS: $Id: Crypt.php 266610 2008-09-21 16:18:57Z cweiske $
 * @link     http://pear.php.net/package/HTML_Crypt
 */


/**
 * HTML_Crypt
 *
 * HTML_Crypt provides methods to encrypt text, which
 * can be later be decrypted using JavaScript on the client side
 *
 * This is very useful to prevent spam robots collecting email
 * addresses from your site, included is a method to add mailto
 * links to the text being generated.
 *
 * The "encryption" function is basically works like ROT13,
 * with the difference that the $offset setting replaces the 13.
 * It is also limited to ASCII characters between 32 and 127 (included).
 * Other characters will not be encrypted.
 *
 * a basic example to encrypt an email address
 * $c = new HTML_Crypt('yourname@emailaddress.com', 8);
 * $c->addMailTo();
 * $c->output();
 *
 * @category HTML
 * @package  HTML_Crypt
 * @author   Michael Dransfield <mike@blueroot.net>
 * @license  http://www.php.net/license  PHP License
 * @link     http://pear.php.net/package/HTML_Crypt
 */
class HTML_Crypt
{
    // {{{ properties

    /**
     * The unencrypted text
     *
     * @access public
     * @var    string
     * @see    setText()
     */
    var $text = '';

    /**
     * The full javascript to be sent to the browser
     *
     * @access public
     * @var    string
     * @see    getScript()
     */
    var $script = '';


    /**
     * The text encrypted - without any js
     *
     * @access public
     * @var    string
     * @see    cyrptText
     */
    var $cryptString = '';


    /**
     * The number to offset the text by
     *
     * @access public
     * @var    int
     */
    var $offset;

    /**
     * Whether or not to use JS for encryption or simple html
     *
     * @access public
     * @var    int
     */
    var $useJS;

    /**
     * a preg expression for an <a href=mailto: ... tag
     *
     * @access public
     * @var    string
     */
     var $apreg;

    /**
     * a preg expression for an email
     *
     * @access public
     * @var    string
     */
    var $emailpreg;

    // }}}
    // {{{ HTML_Crypt()

    /**
     * Constructor
     *
     * @param string  $text   The text to encrypt
     * @param int     $offset The offset used to encrypt/decrypt
     * @param boolean $JS     If javascript shall be used on the client side
     *
     * @access public
     */
    function HTML_Crypt($text = '', $offset = 3, $JS = true)
    {
        $this->offset    = $offset % 95;
        $this->text      = $text;
        $this->script    = '';
        $this->useJS     = $JS;
        $this->emailpreg = '[-_a-z0-9]+(\.[-_a-z0-9]+)*'
                         . '@[-a-z0-9]+(\.[-a-z0-9]+)*\.[a-z]{2,6}';
        $this->apreg     = '\<[aA]\shref=[\"\']mailto:.*\<\/[aA]\>';
    }

    // }}}
    // {{{ setText()

    /**
     * Set name of the current realm
     *
     * @param string $text The text to be encrypted
     *
     * @return void
     *
     * @access public
     */
    function setText($text)
    {
        $this->text = $text;
    }

    // }}}
    // {{{ addMailTo()

    /**
     * Turns the text into a mailto link (make sure
     * the text only contains an email).
     *
     * This method has an optional parameter that allows you
     * to customize the email tag and tag text. To get the email
     * address included, use "%email%' as template variable.
     *
     * @param string $template Mailto template string
     *
     * @return void
     *
     * @access public
     */
    function addMailTo($template = '<a href="mailto:%email%">%email%</a>')
    {
        $email      = $this->text;
        $this->text = str_replace('%email%', $email, $template);
    }

    // }}}
    // {{{ cryptText()

    /**
     * Encrypts the text
     *
     * @param string $text   Text to encrypt
     * @param int    $offset Offset to use for encryption
     *
     * @return string Encrypted text
     * @access private
     */
    function cryptText($text, $offset)
    {
        $enc_string = '';
        $length     = strlen($this->text);

        for ($i=0; $i < $length; $i++) {
            $current_chr = substr($this->text, $i, 1);
            $num         = ord($current_chr);
            if ($num < 128) {
                $inter = $num + $this->offset;
                if ($inter > 127) {
                    $inter = ($inter - 32) % 95 + 32;
                }
                $enc_char    =  chr($inter);
                $enc_string .= ($enc_char == '\\' ? '\\\\' : $enc_char);
            } else {
                $enc_string .= $current_chr;
            }
        }
        return $enc_string;
    }

    // }}}
    // {{{ getScript()

    /**
     * Returns the script html source including the function
     * to decrypt it.
     *
     * @return string $script The javascript generated
     *
     * @access public
     */
    function getScript()
    {
        if ($this->cryptString == '' && $this->text != '') {
            $this->cryptString = $this->cryptText($this->text, $this->offset);
        }
        $letters = array(
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
        );
        $rnd     = $letters[array_rand($letters)] . md5(time());

        // the actual js (in one line to confuse)
        $script = '<script language="JavaScript" type="text/javascript">'
            . '/*<![CDATA[*/'
            . 'var a,s,n;'
            . 'function ' . $rnd . '(s){'
                . 'r="";'
                . 'for(i=0;i<s.length;i++){'
                    . 'n=s.charCodeAt(i);'
                    . 'if(n<128){'
                        . 'n=n-' . $this->offset . ';'
                        . 'if(n<32){'
                            . 'n=127+(n-32);'
                        . '}'
                    . '}'
                    . 'r+=String.fromCharCode(n);'
                . '}'
                . 'return r;'
            . '}'
            . 'a="' . str_replace('"', '\\"', $this->cryptString) . '";'
            . 'document.write(' . $rnd . '(a));'
            . '//]]></script>';

        $this->script = $script;
        return $script;
    }

    // }}}
    // {{{ output()

    /**
     * Outputs the full JS to the browser
     *
     * @return void
     *
     * @access public
     */
    function output()
    {
        echo $this->getOutput();
    }

    // }}}
    // {{{ getOutput()

    /**
     * Returns the encrypted text.
     *
     * @return string Encrypted text
     */
    function getOutput()
    {
        if ($this->useJS) {
            if ($this->script == '') {
                $this->getScript();
            }
            return $this->script;
        } else {
            return str_replace(
                array('@', '.'),
                array(' ^at^ ', '-dot-'),
                $this->text
            );
        }
    }

    // }}}

    /**
     * Starts output buffering.
     *
     * @return void
     */
    function obStart()
    {
        ob_start();
    }

    /**
     * Ends output buffering and echoes the captured text.
     *
     * @return void
     */
    function obEnd()
    {
        $text = ob_get_contents();
        $text = preg_replace_callback(
            "/{$this->apreg}/",
            array($this, '_fly'),
            $text
        );
        ob_end_clean();
        echo $text;
    }

    /**
     * Creates a new crypt object, sets the text on it
     * and returns the script in one step.
     *
     * @param string $text Text to crypt
     *
     * @return string Crypted script
     */
    function _fly($text)
    {
        $c = new HTML_Crypt($text[0]);
        $c->setText($text[0]);
        return $c->getScript();
    }
}
?>
