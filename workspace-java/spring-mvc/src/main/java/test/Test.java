package test;

import java.util.Date;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import edu.rylynn.hasy.dao.impl.UserDaoImpl;
import edu.rylynn.hasy.entity.User;

public class Test {
	public static void main(String[] args)
	{
		ApplicationContext ctx = new ClassPathXmlApplicationContext("application-context.xml");
		
		UserDaoImpl userdao = (UserDaoImpl)ctx.getBean("userDaoImpl");
		User user = new User();
		user.setUsername("rylynn");
		user.setPassword("admin");
		user.setLasttime(new Date());
		userdao.updateUser(user);
	}
}
