package edu.rylynn.hasy.dao.impl;

import static org.springframework.data.mongodb.core.query.Criteria.where;
import static org.springframework.data.mongodb.core.query.Query.query;
import static org.springframework.data.mongodb.core.query.Update.update;

import java.util.Date;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.stereotype.Repository;

import edu.rylynn.hasy.dao.UserDao;
import edu.rylynn.hasy.entity.User;

@Repository
public class UserDaoImpl implements UserDao{
	@Autowired
	private MongoTemplate template;
	
	public void createUser(User user) {
		user.setActive(true);
		user.setLasttime(new Date());
		template.insert(user);
	}

	public User findUserByUsername(String username) {
		User user = template.findOne(query(where("username").is(username)) ,User.class);
		return user;
	}
	
	public void updateUser(String username ,long account)
	{
		template.updateFirst(query(where("username").is(username)), update("account",account), User.class);
	}
	
	public void updateUser(String username ,String password)
	{
		template.updateFirst(query(where("username").is(username)), update("password",password), User.class);
	}
	
	public void updateUser(String username ,boolean active)
	{
		template.updateFirst(query(where("username").is(username)), update("active",false), User.class);
	}
	
	public void updateUser(User newuser)
	{
		User olduser = this.findUserByUsername(newuser.getUsername());
		template.updateFirst(query(where("username").is(olduser.getUsername())), 
				update("lasttime",newuser.getLasttime()), User.class);
		template.updateFirst(query(where("username").is(olduser.getUsername())), 
				update("active",newuser.isActive()), User.class);
		template.updateFirst(query(where("username").is(olduser.getUsername())), 
				update("account",newuser.getAccount()), User.class);
	}

	public List<User> findAllUser() {
		return template.findAll(User.class);
	}
}
