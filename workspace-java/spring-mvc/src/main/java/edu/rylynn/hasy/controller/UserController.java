package edu.rylynn.hasy.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import edu.rylynn.hasy.entity.User;
import edu.rylynn.hasy.exceptions.UserNotExistException;
import edu.rylynn.hasy.service.impl.UserServiceImpl;

@Controller
public class UserController {
	
	@Autowired
	private UserServiceImpl userservice; 
	
	@RequestMapping(value="/stop.do*" ,method=RequestMethod.GET)
	public ModelAndView stopUser(@RequestParam("name")String username)
	{
		ModelAndView mav = new ModelAndView();
		System.out.println(username);
		try {
			
			mav.setViewName("admin");
			mav.addObject("user", userservice.findAllUser());
			User user = userservice.findUserByUsername(username);
			user.setActive(!user.isActive());
			userservice.updateUser(user);
			
		} catch (UserNotExistException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return mav;
	}
}
