<?php

/**
 * @file
 * The action class implements
 */

abstract class WeixinAction {
  private $_request = NULL;
  private $_response = NULL;
  private $_eventCode = 0;

  function __construct($request, $eventCode = 0) {
    $this->_request = $request;
    $this->_eventCode = $eventCode;
    // TODO configable response class
    $this->_response = new WeixinTextResponse();
  }

  /**
   * execute this action
   */
  abstract public function execute();

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

class WeixinNotFoundAction extends WeixinAction {
  public function execute() {
    // nothing todo
  }
}
