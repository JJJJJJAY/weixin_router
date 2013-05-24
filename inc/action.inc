<?php

/**
 * @file
 * The action class implements
 */

interface WeixinActionInterface {
  /**
   * execute this action
   */
  public function execute();
}


abstract class WeixinAction implements WeixinActionInterface {
  private $_request = NULL;
  private $_response = NULL;

  function __construct($request, $response = NULL) {
    $this->_request = $request;
    // TODO configable response class
    if ($response) {
      $this->_response = $response;
    }
    else {
      $this->_response = new WeixinTextResponse();
    }
  }

  /**
   * execute this action
   */
  public function execute() {}

  /**
   * send result by response object
   */
  public function sendResponse() {
    $this->_response->send();
  }

  // response getter
  public function getResponse() {
    return $this->_response;
  }

  // request getter
  public function getRequest() {
    return $this->_request;
  }
}

class WeixinNotFoundAction extends WeixinAction implements WeixinActionInterface {
  public function execute() {
    // nothing todo
  }
}
