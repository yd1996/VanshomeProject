<?php
$root_path=dirname(dirname(__FILE__));
require($root_path.'/businesslogic/TaskInfo.inc');
$task_info=new TaskInfo();
$result = $task_info->detail('task00000001');
echo $result;
$value=array('success'=>1,'msg'=>'查询成功','result'=>$result);
echo $value['result'];
?>
