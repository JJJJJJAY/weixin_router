<?php

/**
 * @file
 * weixin request class
 */

class WeixinRequest {

  private $_xml = NULL;

  function __construct() {
  }

  /**
   * get request by xml that supply by raw_post_data
   */
  public static function requestFromPost() {
    global $HTTP_RAW_POST_DATA;
    $request = new WeixinRequest();
    $request->loadByXml($HTTP_RAW_POST_DATA);
    return $request;
  }

  public function loadByXml($xmlString) {
    if (!empty($xmlString)) {
      // build weixin request object
      $xml = simplexml_load_string($xmlString, 'SimpleXMLElement', LIBXML_NOCDATA);

      $this->_xml = $xml;
    }
  }

  public function getParam($name) {
    if ($this->_xml && isset($this->_xml->$name)) {
      return $this->_xml->$name;
    }
    else {
      return NULL;
    }
  }
}
