package edu.rylynn.hasy.service.impl;

import java.util.Date;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import edu.rylynn.hasy.dao.impl.UserDaoImpl;
import edu.rylynn.hasy.entity.User;
import edu.rylynn.hasy.exceptions.UserExistException;
import edu.rylynn.hasy.exceptions.UserNotExistException;
import edu.rylynn.hasy.service.UserService;
/*
 * 这个类的重复代码太多，我认为是有改进措施的，尤其是对用户名
 * 存在与否的异常的处理，但是因为我今晚太困了，打算改天再思考
 * */
@Service
public class UserServiceImpl implements UserService {

	@Autowired
	private UserDaoImpl userdao;

	public void registerUser(User user) throws UserExistException {
		String username = user.getUsername();
		if (userdao.findUserByUsername(username) == null) {
			user.setActive(true);
			user.setLasttime(new Date());
			userdao.createUser(user);
		} else {
			throw new UserExistException(user.getUsername() + " has exist!");
		}
	}

	public User findUserByUsername(String username) throws UserNotExistException {
		User user = userdao.findUserByUsername(username);
		if (user == null) {
			throw new UserNotExistException(username + " not exist!");

		} else {
			return user;
		}
	}

	public boolean checkPassword(String username, String password) throws UserNotExistException {
		User user = userdao.findUserByUsername(username);
		if (user == null) {
			throw new UserNotExistException(username + " not exist!");

		} else {
			return password.equals(user.getPassword());
		}
	}

	public void ChangePassword(String username, String oldpassword, String newpassword) throws UserNotExistException {
		User user = userdao.findUserByUsername(username);
		if (user == null) {
			throw new UserNotExistException(username + " not exist!");
			
		}
		else
		{
			if(oldpassword.equals(user.getPassword()) == true)
			{
				userdao.updateUser(username, newpassword);
			}
		}
	}

	public long queryAccount(String username) throws UserNotExistException {
		User user = userdao.findUserByUsername(username);
		if (user == null) {
			throw new UserNotExistException(username + " not exist!");
			
		}
		else
		{
			return user.getAccount();
		}
	}

	public List<User> findAllUser() {
		return userdao.findAllUser();
	}

	public void updateUser(User newuser) {
		userdao.updateUser(newuser);
	}

}
