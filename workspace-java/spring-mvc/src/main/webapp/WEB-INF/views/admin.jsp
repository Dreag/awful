<%@ page language="java" contentType="text/html; charset=utf-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ page isELIgnored="false"%>

<!DOCTYPE html>
<html lang="zh-cn">

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Home Page</title>
    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">
    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
            <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.2/html5shiv.min.js"></script>
            <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
        <![endif]-->
</head>

<body>
    <nav class="navbar navbar-default" role="navigation">
        <div class="container-fluid">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="#">Hasy Fondation</a>
            </div>
            <!-- Collect the nav links, forms, and other content for toggling -->
            <div class="collapse navbar-collapse navbar-ex1-collapse">
                <form class="navbar-form navbar-left" role="search">
                    <div class="form-group">
                        <input type="text" class="form-control" placeholder="Search">
                    </div>
                    <button type="submit" class="btn btn-default">Submit</button>
                </form>
                <ul class="nav navbar-nav navbar-right">
                    <li class="dropdown">
                        <a href="#" class="dropdown-toggle" data-toggle="dropdown">更多 <b class="caret"></b></a>
                        <ul class="dropdown-menu">
                            <li><a href="#">Action</a></li>
                            <li><a href="#">Another action</a></li>
                            <li><a href="#">Something else here</a></li>
                            <li><a href="#">Separated link</a></li>
                        </ul>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
    </nav>
    <div class="panel panel-default">
        <div class="panel-heading">
            <h3 class="panel-title">
           <h3 class="text-center">Welcome Rylynn</h3>
            </h3>
        </div>
        <div class="panel-body">
             <h1 class="text-center">Admin Center</h1>
        <div class="container-fluid">
            <div class="row">
                <div class="col-xs-12 col-sm-12 col-md-12 col-lg-12">
                    <table class="table">
                        <caption>This is your System ,rylynn</caption>
                        <thead>
                            <tr>
                                <td>Username</td>
                                <td>Account</td>
                                <td>Last Login Time</td>
                                <td>Status</td>
                            </tr>
                        </thead>
                        <tbody>
                        <c:forEach items="${user}" var="u">
                            <tr>
                                <td>${u.username}</td>
                                <td>${u.account}</td>
                                <td>${u.lasttime}</td>
                                <td>${u.active}</td>
                                <td><a href="stop.do?name=${u.username}"><button type="button" class="btn btn-default">manager</button></a></td>
                            </tr>
                        </c:forEach>
                        </tbody>
                    </table>
                    
                </div>
            </div>
        </div>
        </div>
        <div class="panel-body">
            <form action="moneyadmin.do" method="POST" class="form-inline" role="form">       
                    <div class="form-group">
                        <div class="col-sm-10 col-sm-offset-2">
                        管理系统总资产,设为:<input type="number" name="money" id="inputMoney" class="form-control" min="0" max="999999" required="required" >
                            <button type="submit" class="btn btn-primary">提交</button>
                        </div>
                    </div>
            </form>
        </div>
        <div class="panel-body">
            <form action="useradmin.do" method="POST" class="form-inline" role="form">
            
                <div class="form-group">
                    <div class="col-sm-10 col-sm-offset-2">
                        您要修改的用户名:<input type="text" name="username" class="form-control" required="required" >
                        设置其余额为:<input type="number" name="account" class="form-control" min="0" max="999999" required="required" >
                            <button type="submit" class="btn btn-primary">提交</button>
                      
                
                      </div>
                </div>

            </form>
        </div>
    </div>
    <!-- jQuery -->
    <script src="//code.jquery.com/jquery.js"></script>
    <!-- Bootstrap JavaScript -->
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" integrity="sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS" crossorigin="anonymous"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
</body>

</html>