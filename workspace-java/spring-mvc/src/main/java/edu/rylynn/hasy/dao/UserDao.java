package edu.rylynn.hasy.dao;

import java.util.List;

import edu.rylynn.hasy.entity.User;

public interface UserDao {
	public void createUser(User user);
	
	public User findUserByUsername(String username);
	
	public void updateUser(String username ,long account);
	
	public void updateUser(String username ,String password);
	
	public List<User> findAllUser();
}
