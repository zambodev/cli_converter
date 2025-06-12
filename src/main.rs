use std::{env, u128};
mod parser;


fn main() {
    let mut p= parser::Parser::new();

    // Set command line options
    p.add("-h", "--help", parser::ArgType::Bool(false));

    // Parse given command line options 
    match p.parse(env::args().collect()) {
        Err(e) => return println!("{}", e),
        _ => ()
    }

    let params = match p.get_params() {
        Ok(val) => val,
        Err(e) => return println!("{}", e)
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
        Err(e) => return println!("{}", e)
    };

    if params.len() == 2 {
        match params[1].as_str() {
            "16" => println!("Hex: {:x}", number),
            "10" => println!("Dec: {}", number),
            "8" => println!("Oct: {:o}", number),
            "2" => println!("Bin: {:b}", number),
            _ => return println!("Wrong base parameter!")
        }
    } else {
        println!("Hex: {:x}", number);
        println!("Dec: {}", number);
        println!("Oct: {:o}", number);
        println!("Bin: {:b}", number);
    }

}