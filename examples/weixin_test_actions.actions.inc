<?php

/**
 * @file
 * The actions implements
 */
class HelloAction extends WeixinAction implements WeixinActionInterface {
  public function execute() {
    $response = $this->getResponse();

    $fromUserName = $this->getRequest()->getParam('FromUserName');
    $toUserName = $this->getRequest()->getParam('ToUserName');

    $response->content = "hello $fromUserName";
    $response->fromUserName = $toUserName;
    $response->toUserName = $fromUserName;
  }
}

/**
 * default action
 */
class DefaultAction extends WeixinAction implements WeixinActionInterface {
  public function execute() {
    $response = $this->getResponse();

    $fromUserName = $this->getRequest()->getParam('FromUserName');
    $toUserName = $this->getRequest()->getParam('ToUserName');

    $response->content = "default content";
    $response->fromUserName = $toUserName;
    $response->toUserName = $fromUserName;
  }
}
