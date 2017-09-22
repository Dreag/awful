package edu.rylynn.hasy.controller;

import java.util.Date;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import edu.rylynn.hasy.entity.User;
import edu.rylynn.hasy.exceptions.UserNotExistException;
import edu.rylynn.hasy.service.impl.UserServiceImpl;

/*
 * 这段代码的问题在于我在想service应该定义他的接口类还是实现类
 * 经过我思考后，我认为应该定义接口类，这样如果要该实现，只需要修改实现类的名字即可
 * */
@Controller
public class LoginController {
	
	@Autowired
	UserServiceImpl userservice;
	
	@RequestMapping(value="/home")
	public String homepage()
	{
		return "/";
	}
	
	@RequestMapping(value="/register.do" ,method=RequestMethod.POST)
	public String register(@RequestParam("username")String username ,@RequestParam("password")String password)
	{
		User user = new User();
		user.setActive(true);
		user.setAccount(50);
		user.setLasttime(new Date());
		user.setPassword(password);
		user.setUsername(username);
		return "/";
	}
	@RequestMapping(value="/login.do" ,method=RequestMethod.POST)
	public ModelAndView login(@RequestParam("username")String username ,@RequestParam("password") String password)
	{

		//System.out.println(username);
		ModelAndView mav = new ModelAndView();
		try {
			User user = userservice.findUserByUsername(username);
			if(userservice.checkPassword(username, password) == true)
			{
				if(user.getUsername().equals("rylynn"))
				{
					user.setLasttime(new Date());
					userservice.updateUser(user);
					mav.setViewName("admin");
					mav.addObject("user", userservice.findAllUser());
					return mav;
				}
				else
				{
					mav.setViewName("user");
					return mav;
				}
			}
			mav.setViewName("login-fail");
			return mav;
		} catch (UserNotExistException e1 ) {
			// TODO Auto-generated catch block
			mav.setViewName("login-fail");
			return mav;
		}
		
	}
}
