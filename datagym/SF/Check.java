/******************************************************************/
/* ACM ICPC 2015-2016, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 24, 2015                                */
/******************************************************************/
/* Problem F. Fygon                                               */
/*                                                                */
/* Original idea         Pavel Mavrin                             */
/* Problem statement     Pavel Mavrin                             */
/* Test set              Pavel Mavrin                             */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.*;

import java.math.BigInteger;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Check implements Checker {

    private static final int MAX_LENGTH = 100;

    public Outcome outcome(Outcome.Type type, final String format, final Object... args) {
        return new Outcome(type, String.format(format, args));
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        Polynomial jury = null;
        try {
            jury = parse(ans.nextLine());
        } catch (ParseException e) {
            return outcome(FAIL, e.getMessage());
        }
        Polynomial user = null;
        try {
            user = parse(ouf.nextLine());
        } catch (ParseException e) {
            return outcome(WA, e.getMessage());
        }
        if (!jury.equals(user)) {
            return outcome(WA, "Expected " + jury.toString() + " found " + user.toString());
        }
        return outcome(OK, jury.toString());
    }

    private Polynomial parse(String s) throws ParseException {
        s = compress(s);
        if (s.length() > MAX_LENGTH) throw new ParseException("String is too long", -1);
        this.s = s + ".";
        pos = 0;
        Polynomial res = parseExpression();
        if (pos != s.length()) {
            throw new ParseException("Extra characters after " + pos + ": '" + current() + "'", pos);
        }
        return res;
    }

    private Polynomial parseExpression() throws ParseException {
        Polynomial res = parseProduct();
        while (current() == '+' || current() == '-') {
            if (current() == '+') {
                next();
                res = res.add(parseProduct());
            } else {
                next();
                res = res.subtract(parseProduct());
            }
        }
        return res;
    }

    private Polynomial parseProduct() throws ParseException {
        Polynomial res = parseValue();
        while (current() == '*') {
            next();
            res = res.multiply(parseValue());
        }
        return res;
    }

    private Polynomial parseValue() throws ParseException {
        if (current() == 'n') {
            next();
            return N;
        } else if (current() == '-') {
            next();
            return parseValue().negate();
        } else if (current() >= '0' && current() <= '9') {
            BigInteger p = parseInteger();
            BigInteger q = BigInteger.ONE;
            if (current() == '/') {
                next();
                q = parseInteger();
                if (q.equals(BigInteger.ZERO)) {
                    throw new ParseException("Division by zero", pos);
                }
            }
            Polynomial res = new Polynomial();
            res.c.add(new Rational(p, q));
            return res;
        } else if (current() == '(') {
            next();
            Polynomial res = parseExpression();
            if (current() != ')') throw new ParseException("Unexpected " + current() + " instead of )", pos);
            next();
            return res;
        } else {
            throw new ParseException("Unexpected " + current(), pos);
        }
    }

    private BigInteger parseInteger() throws ParseException {
        if (current() < '0' || current() > '9') throw new ParseException("Unexpected " + current() + " instead of digit", pos);
        BigInteger res = BigInteger.valueOf(current() - '0');
        next();
        while (current() >= '0' && current() <= '9') {
            res = res.multiply(BigInteger.TEN).add(BigInteger.valueOf(current() - '0'));
            next();
        }
        return res;
    }

    private void next() {
        pos++;
    }

    private char current() {
        return s.charAt(pos);
    }

    String s;
    int pos;

    private String compress(String s) {
        StringBuilder sb = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (!Character.isWhitespace(c)) {
                sb.append(c);
            }
        }
        return sb.toString();
    }

    class Polynomial {
        List<Rational> c;

        public Polynomial(List<Rational> c) {
            this.c = c;
            while (c.size() > 0 && c.get(c.size() - 1).p.signum() == 0) {
                c.remove(c.size() - 1);
            }
        }

        public Polynomial() {
            c = new ArrayList<>();
        }

        public Polynomial negate() {
            Polynomial res = new Polynomial();
            for (Rational cc : c) {
                res.c.add(cc.negate());
            }
            return res;
        }

        public Polynomial add(Polynomial o) {
            List<Rational> res = new ArrayList<>();
            for (int i = 0; i < Math.min(c.size(), o.c.size()); i++) {
                res.add(c.get(i).add(o.c.get(i)));
            }
            for (int i = res.size(); i < c.size(); i++) {
                res.add(c.get(i));
            }
            for (int i = res.size(); i < o.c.size(); i++) {
                res.add(o.c.get(i));
            }
            return new Polynomial(res);
        }

        public Polynomial subtract(Polynomial o) {
            return add(o.negate());
        }

        public Polynomial multiply(Polynomial o) {
            List<Rational> res = new ArrayList<>();
            for (int i = 0; i < c.size() + o.c.size() - 1; i++) {
                Rational q = new Rational(0, 1);
                for (int j = 0; j < c.size(); j++) {
                    int k = i - j;
                    if (k >= 0 && k < o.c.size()) {
                        q = q.add(c.get(j).multiply(o.c.get(k)));
                    }
                }
                res.    add(q);
            }
            return new Polynomial(res);
        }

        @Override
        public boolean equals(Object obj) {
            Polynomial o = (Polynomial) obj;
            if (o.c.size() != c.size()) return false;
            for (int i = 0; i < c.size(); i++) {
                if (!c.get(i).equals(o.c.get(i))) return false;
            }
            return true;
        }

        @Override
        public String toString() {
            if (c.size() == 0) return "0";
            StringBuilder res = new StringBuilder();
            boolean first = true;
            for (int i = c.size() - 1; i >= 0; i--) {
                if (c.get(i).p.signum() != 0) {
                    if (!first) {
                        res.append(" ").append(c.get(i).p.signum() > 0 ? "+" : "-").append(" ");
                    }
                    first = false;
                    if (i > 0 && c.get(i).p.abs().equals(BigInteger.ONE) && c.get(i).q.equals(BigInteger.ONE)) {
                        res.append("n");
                        for (int j = 0; j < i - 1; j++) {
                            res.append("*n");
                        }
                    } else {
                        res.append(c.get(i).p.abs());
                        if (!c.get(i).q.equals(BigInteger.ONE)) {
                            res.append("/").append(c.get(i).q);
                        }
                        for (int j = 0; j < i; j++) {
                            res.append("*n");
                        }
                    }
                }
            }
            return res.toString();
        }
    }

    Polynomial ONE;
    Polynomial N;
    {
        ONE = new Polynomial();
        ONE.c.add(new Rational(1, 1));
        N = new Polynomial();
        N.c.add(new Rational(0, 1));
        N.c.add(new Rational(1, 1));
    }

    class Rational {
        BigInteger p;
        BigInteger q;

        public Rational(BigInteger p, BigInteger q) {
            if (q.signum() < 0) {
                q = q.negate();
                p = p.negate();
            }
            BigInteger d = p.gcd(q);
            this.p = p.divide(d);
            this.q = q.divide(d);
        }

        public Rational(long p, long q) {
            this(BigInteger.valueOf(p), BigInteger.valueOf(q));
        }

        public Rational divide(Rational o) {
            return new Rational(p.multiply(o.q), q.multiply(o.p));
        }

        public Rational multiply(Rational o) {
            return new Rational(p.multiply(o.p), q.multiply(o.q));
        }

        public Rational subtract(Rational o) {
            return new Rational(p.multiply(o.q).subtract(o.p.multiply(q)), q.multiply(o.q));
        }

        @Override
        public String toString() {
            return p + "/" + q;
        }

        public Rational negate() {
            return new Rational(p.negate(), q);
        }

        public Rational add(Rational o) {
            return new Rational(p.multiply(o.q).add(o.p.multiply(q)), q.multiply(o.q));
        }

        @Override
        public boolean equals(Object o) {
            return p.equals(((Rational)o).p) & q.equals(((Rational)o).q);
        }
    }


}

