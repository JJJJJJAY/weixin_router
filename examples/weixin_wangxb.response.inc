<?php

/**
 * @file
 * default special response class for weixin_wangxb module
 */

class WangxbActicleResponse extends WeixinArticleResponse {
  public function getImageUri($item) {
    return $item->field_blog_image['und'][0]['uri'];
  }
  public function getBodyValue($item) {
    return $item->body['und'][0]['value'];
  }
}
