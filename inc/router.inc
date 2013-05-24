<?php

/**
 * @file
 * weixin router class
 */

class WeixinException extends Exception {}

/**
 * weixin router base class
 */
class WeixinRouter {
  private $_request = NULL;
  private $_actions = array();
  private $_defaultAction = NULL;
  private static $_instance = NULL;

  // request setter
  public function setRequest($request) {
    $this->_request = $request;
  }
  // actions setter
  public function setActions($actions) {
    $this->_actions = $actions;
  }
  // default action setter and getter
  public function setDefaultAction(WeixinActionInterface $action) {
    $this->_defaultAction = $action;
  }
  public function getDefaultAction() {
    if ($this->_defaultAction) {
      return $this->_defaultAction;
    }
    return FALSE;
  }

  // actions getter
  public function getActions() {
    if (empty($this->_actions)) {
      $this->_actions = module_invoke_all('weixin_router_actions');
    }
    return $this->_actions;
  }

  /**
   * The singleton factory method, get instance
   */
  public static function load() {
    if (self::$_instance === NULL) {
      self::$_instance = new WeixinRouter();
    }
    return self::$_instance;
  }

  /**
   * do dispatch
   */
  public function dispatch() {
    // build target action object
    $this->_request = WeixinRequest::requestFromPost();
    $action = $this->getAction();

    // call action object execute method
    $action->execute();

    // send response
    $action->sendResponse();
  }

  /**
   * get action by request
   * @param WeixinRequest $request
   * @return WeixinAction
   */
  public function getAction() {
    $request = $this->_request;

    $msgtype = $request->getParam('MsgType');
    $event = '0';
    switch($msgtype) {
      case 'text':
        $event = $this->_textParseToEvent($request->getParam('Content'));
        break;
      case 'event':
        $event = $request->getParam('Event');
        break;
      case 'image':
      case 'location':
      case 'url':
      default:
        return new WeixinNotFoundAction($request);
    }
    return $this->getActionByEvent($event);
  }

  /**
   * get action by event code
   * @param string $event event code
   * @return WeixinAction
   */
  public function getActionByEvent($event) {
    $actions = $this->getActions();

    foreach ($actions as $actionEvent => $action) {
      if ($event == $actionEvent) {
        $class = $action['class'];
        return new $class($this->_request, $event);
      }
    }
    if ($action = $this->getDefaultAction()) {
      return $action;
    }
    throw new WeixinException('event code doesn\'t exist: event code \'' . $event . '\'');
  }

  /**
   * parse content to event code
   * @param string $text common text
   * @return string
   */
  protected function _textParseToEvent($text) {
    return $text;
  }
}
