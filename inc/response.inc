<?php

/**
 * @file
 * The response class implements
 */

/**
 * The base response class
 */
abstract class WeixinResponse {
  public $toUserName;
  public $fromUserName;
  public $msgType;

  private $_body = NULL;
  private $_header = NULL;

  abstract public function build();

  // get and set for body
  public function setBody($body) {
    $this->_body = $body;
  }
  public function getBody() {
    return $this->_body;
  }

  public function sendHeader() {
  }

  public function sendBody() {
    $this->build();
    echo $this->_body;
  }

  /**
   * print a string to page callback, this string is a xml
   */
  public function send() {
    $this->sendHeader();
    $this->sendBody();
  }
}

/**
 * The text message response class
 */
class WeixinTextResponse extends WeixinResponse {
  public $content = '';

  public function build() {
    $xmlTpl = "<xml>
<ToUserName><![CDATA[%s]]></ToUserName>
<FromUserName><![CDATA[%s]]></FromUserName>
<CreateTime>%s</CreateTime>
<MsgType><![CDATA[text]]></MsgType>
<Content><![CDATA[%s]]></Content>
<FuncFlag>0</FuncFlag>
</xml>";

    $this->setBody(sprintf($xmlTpl,
        $this->toUserName,
        $this->fromUserName,
        REQUEST_TIME,
        $this->content
      ));
  }
}
