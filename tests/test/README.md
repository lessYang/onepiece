## 数据库导出
mysqldump -u userName -p databaseName > databaseName.sql

## 数据库导入

1. 方法一
     mysql -u userName -p databaseName < databaseName.sql
2. 方法二
    进入mysql
    source path/databaseName.sql

## 测试方法
1. 本地或者测试机器安装mysql
2. 将需要的数据导入mysql, 注意修改dbconfig表, 修改地址、用户、密码
3. 修改testclient.conf文件，配置正确的信息
4. 测试

## 测试内容
1. 接口功能的准确性
2. 日志格式，内容准确性
3. 效率
