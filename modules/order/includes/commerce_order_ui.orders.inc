<?php
// $Id$

/**
 * @file
 * Page callbacks and form builder functions for administering orders.
 */


/**
 * Form callback: edit the global order settings.
 */
function commerce_order_settings_form($form, &$form_state) {
  $form['commerce_order_help_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Order creation help text'),
    '#description' => t('Supply an optional help message to be displayed above the order add form.'),
    '#default_value' => variable_get('commerce_order_help_text', ''),
  );

  return system_settings_form($form);
}

/**
 * Form callback wrapper: create or edit an order.
 *
 * @param $order
 *   The order object to edit through the form.
 * @param $account
 *   For new orders, the customer's user account.
 *
 * @see commerce_order_order_form()
 */
function commerce_order_ui_order_form_wrapper($order, $account = NULL) {
  // Add the breadcrumb for the form's location.
  commerce_order_ui_set_breadcrumb();

  // Set the page title and a default customer if necessary.
  if (empty($order->order_id)) {
    drupal_set_title(t('Create an order'));

    if (!empty($account)) {
      $order->customer_uid = $account->uid;
    }
  }

  // Include the forms file from the Order module.
  module_load_include('inc', 'commerce_order', 'includes/commerce_order.forms');

  return drupal_get_form('commerce_order_ui_order_form', $order);
}

/**
 * Form callback wrapper: confirmation form for deleting an order.
 *
 * @param $order
 *   The order object to delete through the form.
 *
 * @see commerce_order_order_delete_form()
 */
function commerce_order_ui_order_delete_form_wrapper($order) {
  // Add the breadcrumb for the form's location.
  commerce_order_ui_set_breadcrumb();

  // Include the forms file from the Order module.
  module_load_include('inc', 'commerce_order', 'includes/commerce_order.forms');

  return drupal_get_form('commerce_order_ui_order_delete_form', $order);
}