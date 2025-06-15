use std::{env, u128};
use colored::Colorize;
mod parser;


fn main() {
    const HELP_MSG: &str = "Usage: \n\
        \r      conv [OPTIONS] [PREFIX]number \n\
        \r      conv [OPTIONS] [PREFIX]number [BASE] \n\
        \n\
        \rPrefixes: \n\
        \r      0x              16 base number\n\
        \r                      10 base number (no prefix needed)\n\
        \r      0               8 base number\n\
        \r      0b              2 base number\n\
        \n\
        \rBases: \n\
        \r      16              to 16 base\n\
        \r      10              to 10 base\n\
        \r      8               to 8 base\n\
        \r      2               to 2 base\n\
        \n\
        \rOptions: \n\
        \r      -h, --help      Display this message \n\
    ";


    let mut p= parser::Parser::new();

    // Set command line options
    p.add("-h", parser::ArgType::Bool(false));

    // Parse given command line options 
    match p.parse(env::args().collect()) {
        Err(e) => return println!("{}", e.to_string().red()),
        _ => ()
    }

    match p.is_set("-h") {
        Ok(true) => return println!("{}", HELP_MSG),
        Ok(false) => (),
        Err(e) => return println!("{}", e.to_string().red())
    }

    let params = match p.get_params() {
        Ok(val) => val,
        Err(e) => {
            println!("{}", e.to_string().red());
            return println!("{}", HELP_MSG);
        }
    };

    let p = params[0].as_str();
    let (digits, base) = match p {
        _ if p.starts_with("0x") => {
            (p.strip_prefix("0x").unwrap(), 16)
        },
        _ if p.starts_with("0b") => {
            (p.strip_prefix("0b").unwrap(), 2)
        },
        _ if p.starts_with("0") => {
            (p.strip_prefix("0").unwrap(), 8)
        },
        _ => (p, 10)
    };

    let number = match u128::from_str_radix(digits, base) {
        Ok(val) => val,
        Err(e) => return println!("{}", e.to_string().red())
    };

    if params.len() == 2 {
        match params[1].as_str() {
            "16" => println!("hex: {:x}", number),
            "10" => println!("dec: {}", number),
            "8" => println!("oct: {:o}", number),
            "2" => println!("bin: {:b}", number),
            _ => return println!("{}", "wrong base parameter!".red())
        }
    } else {
        println!("hex: {:x}", number);
        println!("dec: {}", number);
        println!("oct: {:o}", number);
        println!("bin: {:b}", number);
    }

}