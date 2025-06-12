use std::{collections::HashMap, u128, fmt};

#[derive(Debug)]
pub enum ArgType {
    Str(String),
    Int(u128),
    Bool(bool)
}

impl Clone for ArgType {
    fn clone(&self) -> Self {
        match self {
            ArgType::Str(val) => ArgType::Str(val.to_string()),
            ArgType::Int(val) => ArgType::Int(*val),
            ArgType::Bool(val) => ArgType::Bool(*val),
        }
    }
}

pub struct ArgError {
    error: String
}

impl fmt::Display for ArgError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.error)
    }
}

#[derive(Debug)]
pub struct Arg {
    is_set: bool,
    shortf: String,
    longf: String,
    value: ArgType 
}

impl Arg {
    pub fn new(shortf: String, longf: String, value: ArgType) -> Arg {
        Arg {
            is_set: false,
            shortf,
            longf,
            value
        }
    }
}

pub struct Parser {
    arglist: HashMap<String, Arg>,
    paramlist: Vec<String>
}

impl Parser {
    fn label_normalize(label: String) -> Option<String> {
        match label {
            _ if label.starts_with("--") => return Some(label[1..3].to_string()),
            _ if label.starts_with("-") =>  return Some(label[0..2].to_string()),
            _ => return None
        };
    }

    pub fn new() -> Parser {
        Parser {
            arglist: HashMap::new(),
            paramlist: vec![]
        }
    }

    pub fn add(&mut self, shortf: &str, longf: &str, default_value: ArgType) {
        self.arglist.insert(shortf.to_string(), Arg{ is_set: false, shortf: shortf.to_string(), longf: longf.to_string(), value: default_value });
    }

    pub fn parse(&mut self, args: Vec<String>) -> Result<(), ArgError> {
        let mut i = 1;
        while i < args.len() {
            match Parser::label_normalize(args[i].clone()) {
                // Parse label
                Some(label) => {
                    let argref= match self.arglist.get_mut(& label) {
                        Some(argument) => argument,
                        None => return Err(ArgError{ error: "Unknown command line options!".to_string() })
                    };

                    match &argref.value {
                        ArgType::Str(_) => {
                            if (i + 1) >= args.len() {
                                return Err(ArgError{ error: "Missing option value!".to_string() });
                            }

                            argref.is_set = true;
                            argref.value = ArgType::Str(args[i + 1].clone());
                            println!("{:?}", argref);

                            i += 1;
                        },
                        ArgType::Int(_) => {
                            if (i + 1) >= args.len() {
                                return Err(ArgError{ error: "Missing option value!".to_string() });
                            }

                            argref.is_set = true;
                            argref.value = ArgType::Int(args[i + 1].parse::<u128>().unwrap());
                            println!("{:?}", argref);

                            i += 1;
                        },
                        ArgType::Bool(_) => {
                            argref.is_set = true;
                            argref.value = ArgType::Bool(true);
                            println!("{:?}", argref);
                        }
                    }
                },
                // Parse positional argument
                None => {
                    self.paramlist.push(args[i].clone());
                }
            }

            i += 1;
        }

        Ok(())
    }

    pub fn is_set(&mut self, label: &str) -> Result<bool, ArgError> {
        let nlabel = match Parser::label_normalize(label.to_string()) {
            Some(val) => val,
            None => return Err(ArgError{ error: "Unknown command line options!".to_string() })
        };

        match self.arglist.get_mut(& nlabel) {
            Some(arg) => return Ok(arg.is_set),
            None => return Err(ArgError{ error: "Unknown command line options!".to_string() })
        };
    }

    pub fn get_option_value(& self, label: String) -> Result<ArgType, ArgError> {
        let argref= match self.arglist.get(& label) {
            Some(argument) => argument,
            None => return Err(ArgError{ error: "Unknown command line options!".to_string() })
        };

        Ok(argref.value.clone())
    }

    pub fn get_params(& self) -> Result<Vec<String>, ArgError> {
        if !self.paramlist.is_empty() {
            Ok(self.paramlist.clone())
        } else {
            return Err(ArgError{ error: "Missing positional parameter!".to_string() })
        }
    }
}
