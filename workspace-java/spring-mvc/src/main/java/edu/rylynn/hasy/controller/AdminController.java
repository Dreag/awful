package edu.rylynn.hasy.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import edu.rylynn.hasy.entity.User;
import edu.rylynn.hasy.exceptions.UserNotExistException;
import edu.rylynn.hasy.service.impl.UserServiceImpl;

@Controller
public class AdminController {

	@Autowired
	private UserServiceImpl userservice;
	
	@RequestMapping("/moneyadmin.do")
	public ModelAndView moneyReset(@RequestParam("money")long money) throws UserNotExistException
	{
		ModelAndView mav = new ModelAndView();
		User admin = userservice.findUserByUsername("rylynn");
		admin.setAccount(money);
		userservice.updateUser(admin);
		mav.setViewName("admin");
		mav.addObject("user" ,userservice.findAllUser());
		return mav;
	}
}
