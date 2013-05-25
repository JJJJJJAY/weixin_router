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


/**
 * The article message response class
 */
abstract class WeixinArticleResponse extends WeixinResponse {
  public $items = array();

  /**
   * get image uri
   */
  abstract public function getImageUri($item);

  /**
   * get body value
   */
  abstract public function getBodyValue($item);

  public function build() {
    $bodyTpl = "<xml>
<ToUserName><![CDATA[%s]]></ToUserName>
<FromUserName><![CDATA[%s]]></FromUserName>
<CreateTime>%s</CreateTime>
<MsgType><![CDATA[news]]></MsgType>
<ArticleCount>%s</ArticleCount>
<Articles>
%s
</Articles>
<FuncFlag>1</FuncFlag>
</xml>";

    $itemTpl = "<item>
<Title><![CDATA[%s]]></Title>
<Description><![CDATA[%s]]></Description>
<PicUrl><![CDATA[%s]]></PicUrl>
<Url><![CDATA[%s]]></Url>
</item>";

    $itemsXml = '';

    foreach ($this->items as $nid => $item) {
      $url = url('node/' . $nid, array('absolute' => TRUE));
      $image_url = file_create_url($this->getImageUri($item));
      // $item->example_node_image['und'][0]['uri']
      $body = $this->getBodyValue($item);
      // $item->body['und'][0]['value']
      $itemsXml .= sprintf($itemTpl,
                   $item->title,
                   $body,
                   $image_url,
                   $url);
    }

    $this->setBody(sprintf($bodyTpl,
        $this->toUserName,
        $this->fromUserName,
        REQUEST_TIME,
        count($this->items),
        $itemsXml));
  }
}

/**
 * default article response, field name of image is 'image', and field name of body is 'body'
 */
class WeixinDefaultArticleResponse extends WeixinArticleResponse {
  public function getImageUri($item) {
    return $item->image['und'][0]['uri'];
  }
  public function getBodyValue($item) {
    return $item->body['und'][0]['value'];
  }
}
