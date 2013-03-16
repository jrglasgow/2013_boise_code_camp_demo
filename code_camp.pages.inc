<?php

/**
 * module created pages
 */

function code_camp_page() {
  $form = drupal_get_form('code_camp_page_form');
  $query = db_select('code_camp');
  $query->fields('code_camp', array('id', 'name','phone','email'));
  $results = $query->execute();
  $people = $results->fetchAllAssoc('id');
  $rows = array();
  foreach ($people AS $person) {
    $rows[] = array(
      $person->id,
      $person->name,
      $person->phone,
      $person->email,
    );
  }
  $output = drupal_render($form);
  $output .= theme('table', array('rows' => $rows, 'header' => array(t('id'), t('Name'), t('Phone'), t('E-mail'))));
  return $output;
}

function code_camp_page_form() {
  $form = array();

  $form['name'] = array(
    '#type'             => 'textfield',
    '#title'            => t('name'),
    '#description'      => t('a person\'s name'),
  );

  $form['phone'] = array(
    '#type'             => 'textfield',
    '#title'            => t('phone'),
    '#description'      => t('a person\'s phone number'),
  );
  $form['email'] = array(
    '#type'             => 'textfield',
    '#title'            => t('email'),
    '#description'      => t('a person\'s e-mail address'),
  );

  $form['submit'] = array(
    '#type'       => 'submit',
    '#value'      => t('Submit'),
  );

  return $form;
}

function code_camp_page_form_submit(&$form, $form_state) {
  $query = db_insert('code_camp');
  $query->fields(array('name' => $form_state['values']['name'],
                       'phone' => $form_state['values']['phone'],
                       'email' => $form_state['values']['email'],));
  $query->execute();
}
