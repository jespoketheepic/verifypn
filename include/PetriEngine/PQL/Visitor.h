/*
 *  Copyright Peter G. Jensen, all rights reserved.
 */

/*
 * File:   Visitor.h
 * Author: Peter G. Jensen <root@petergjoel.dk>
 *
 * Created on April 11, 2020, 1:07 PM
 */

#ifndef VISITOR_H
#define VISITOR_H

#include "PetriEngine/PQL/Expressions.h"
#include "utils/errors.h"
#include <type_traits>

namespace PetriEngine {
    namespace PQL {

        class Visitor {
        public:

            Visitor() {
            }

            template<typename T>
            void accept(T &&element) {
                _accept(element);
            }

            template<typename T, typename Q>
            static void visit(T& visitor, Q c) {
                visit(&visitor, c);
            }

            template<typename T, typename Q>
            static void visit(T* visitor, const std::shared_ptr<Q>& c) {
                visit(visitor, c.get());
            }

            template<typename T, typename Q>
            static void visit(T* visitor, const Q* c) {
                visit(visitor, const_cast<Q*> (c));
            }

            template<typename T, typename Q>
            static void visit_expr(T* visitor, Q* c) {
                switch (c->type()) {
                    case type_id<PlusExpr>():
                        visitor->accept(static_cast<PlusExpr*> (c));
                        break;
                    case type_id<MinusExpr>():
                        visitor->accept(static_cast<MinusExpr*> (c));
                        break;
                    case type_id<SubtractExpr>():
                        visitor->accept(static_cast<SubtractExpr*> (c));
                        break;
                    case type_id<MultiplyExpr>():
                        visitor->accept(static_cast<MultiplyExpr*> (c));
                        break;
                    case type_id<IdentifierExpr>():
                        visitor->accept(static_cast<IdentifierExpr*> (c));
                        break;
                    case type_id<LiteralExpr>():
                        visitor->accept(static_cast<LiteralExpr*> (c));
                        break;
                    case type_id<UnfoldedIdentifierExpr>():
                        visitor->accept(static_cast<UnfoldedIdentifierExpr*> (c));
                        break;
                    default:
                        __builtin_unreachable(); // <-- helps the compiler optimize
                }
            }

            template<typename T, typename Q>
            static void visit(T* visitor, Q* c) {
                if constexpr (std::is_base_of<Expr,Q>::value)
                        visit_expr(visitor, c);
                else
                {
                    switch (c->type()) {
                        case type_id<OrCondition>():
                            visitor->accept(static_cast<OrCondition*> (c));
                            break;
                        case type_id<AndCondition>():
                            visitor->accept(static_cast<AndCondition*> (c));
                            break;
                        case type_id<CompareConjunction>():
                            visitor->accept(static_cast<CompareConjunction*> (c));
                            break;
                        case type_id<LessThanCondition>():
                            visitor->accept(static_cast<LessThanCondition*> (c));
                            break;
                        case type_id<LessThanOrEqualCondition>():
                            visitor->accept(static_cast<LessThanOrEqualCondition*> (c));
                            break;
                        case type_id<EqualCondition>():
                            visitor->accept(static_cast<EqualCondition*> (c));
                            break;
                        case type_id<NotEqualCondition>():
                            visitor->accept(static_cast<NotEqualCondition*> (c));
                            break;
                        case type_id<DeadlockCondition>():
                            visitor->accept(static_cast<DeadlockCondition*> (c));
                            break;
                        case type_id<UnfoldedUpperBoundsCondition>():
                            visitor->accept(static_cast<UnfoldedUpperBoundsCondition*> (c));
                            break;
                        case type_id<NotCondition>():
                            visitor->accept(static_cast<NotCondition*> (c));
                            break;
                        case type_id<BooleanCondition>():
                            visitor->accept(static_cast<BooleanCondition*> (c));
                            break;
                        case type_id<ECondition>():
                            visitor->accept(static_cast<ECondition*> (c));
                            break;
                        case type_id<ACondition>():
                            visitor->accept(static_cast<ACondition*> (c));
                            break;
                        case type_id<FCondition>():
                            visitor->accept(static_cast<FCondition*> (c));
                            break;
                        case type_id<GCondition>():
                            visitor->accept(static_cast<GCondition*> (c));
                            break;
                        case type_id<UntilCondition>():
                            visitor->accept(static_cast<UntilCondition*> (c));
                            break;
                        case type_id<XCondition>():
                            visitor->accept(static_cast<XCondition*> (c));
                            break;
                        case type_id<ControlCondition>():
                            visitor->accept(static_cast<ControlCondition*> (c));
                            break;
                        case type_id<StableMarkingCondition>():
                            visitor->accept(static_cast<StableMarkingCondition*> (c));
                            break;
                        case type_id<QuasiLivenessCondition>():
                            visitor->accept(static_cast<QuasiLivenessCondition*> (c));
                            break;
                        case type_id<LivenessCondition>():
                            visitor->accept(static_cast<LivenessCondition*> (c));
                            break;
                        case type_id<KSafeCondition>():
                            visitor->accept(static_cast<KSafeCondition*> (c));
                            break;
                        case type_id<UpperBoundsCondition>():
                            visitor->accept(static_cast<UpperBoundsCondition*> (c));
                            break;
                        case type_id<FireableCondition>():
                            visitor->accept(static_cast<FireableCondition*> (c));
                            break;
                        case type_id<UnfoldedFireableCondition>():
                            visitor->accept(static_cast<UnfoldedFireableCondition*> (c));
                            break;
                        case type_id<EFCondition>():
                            visitor->accept(static_cast<EFCondition*> (c));
                            break;
                        case type_id<AGCondition>():
                            visitor->accept(static_cast<AGCondition*> (c));
                            break;
                        case type_id<AUCondition>():
                            visitor->accept(static_cast<AUCondition*> (c));
                            break;
                        case type_id<EUCondition>():
                            visitor->accept(static_cast<EUCondition*> (c));
                            break;
                        case type_id<EXCondition>():
                            visitor->accept(static_cast<EXCondition*> (c));
                            break;
                        case type_id<AXCondition>():
                            visitor->accept(static_cast<AXCondition*> (c));
                            break;
                        case type_id<AFCondition>():
                            visitor->accept(static_cast<AFCondition*> (c));
                            break;
                        case type_id<EGCondition>():
                            visitor->accept(static_cast<EGCondition*> (c));
                            break;
                        default:
                            __builtin_unreachable(); // <-- helps the compiler optimize
                    }
                }
            }

            //virtual ~Visitor() = default;

        protected:

            virtual void _accept(const NotCondition* element) {
                assert(false);
                throw base_error("No accept for NotCondition");
            };

            virtual void _accept(const AndCondition* element) {
                _accept(static_cast<const LogicalCondition*> (element));
            }

            virtual void _accept(const OrCondition* element) {
                _accept(static_cast<const LogicalCondition*> (element));
            }

            virtual void _accept(const LessThanCondition* element) {
                _accept(static_cast<const CompareCondition*> (element));
            }

            virtual void _accept(const LessThanOrEqualCondition* element) {
                _accept(static_cast<const CompareCondition*> (element));
            }

            virtual void _accept(const EqualCondition* element) {
                _accept(static_cast<const CompareCondition*> (element));
            }

            virtual void _accept(const NotEqualCondition* element) {
                _accept(static_cast<const CompareCondition*> (element));
            }

            virtual void _accept(const DeadlockCondition* element) {
                assert(false);
                throw base_error("No accept for DeadlockCondition");
            };

            virtual void _accept(const CompareConjunction* element) {
                assert(false);
                throw base_error("No accept for CompareConjunction");
            };

            virtual void _accept(const UnfoldedUpperBoundsCondition* element) {
                assert(false);
                throw base_error("No accept for UndfoldedUpperBoundsCondition (may be called from subclass)");
            };

            // Super classes, the default implementation of subclasses is to call these

            virtual void _accept(const CommutativeExpr *element) {
                _accept(static_cast<const NaryExpr*> (element));
            }

            virtual void _accept(const SimpleQuantifierCondition *element) {
                assert(false);
                std::cerr << "No accept for SimpleQuantifierCondition (may be called from subclass)" << std::endl;
                exit(0);
            }

            virtual void _accept(const LogicalCondition *element) {
                assert(false);
                std::cerr << "No accept for LogicalCondition (may be called from subclass)" << std::endl;
                exit(0);
            }

            virtual void _accept(const CompareCondition *element) {
                assert(false);
                std::cerr << "No accept for CompareCondition (may be called from subclass)" << std::endl;
                exit(0);
            }

            virtual void _accept(const UntilCondition *element) {
                assert(false);
                std::cerr << "No accept for UntilCondition (may be called from subclass)" << std::endl;
                exit(0);
            }


            // Quantifiers, most uses of the visitor will not use the quantifiers - so we give a default implementation.
            // default behaviour is error

            virtual void _accept(const ControlCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const EFCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const EGCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const AGCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const AFCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const EXCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const AXCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const EUCondition *condition) {
                _accept(static_cast<const UntilCondition*> (condition));
            };

            virtual void _accept(const AUCondition *condition) {
                _accept(static_cast<const UntilCondition*> (condition));
            };

            virtual void _accept(const ACondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const ECondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const GCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const FCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const XCondition *condition) {
                _accept(static_cast<const SimpleQuantifierCondition*> (condition));
            };

            virtual void _accept(const ShallowCondition *element) {
                if (element->getCompiled()) {
                    visit(this, element->getCompiled());
                } else {
                    assert(false);
                    std::cerr << "No accept for ShallowCondition" << std::endl;
                    exit(0);
                }
            }

            // shallow elements, neither of these should exist in a compiled expression

            virtual void _accept(const UnfoldedFireableCondition *element) {
                _accept(static_cast<const ShallowCondition*> (element));
            };

            virtual void _accept(const FireableCondition *element) {
                _accept(static_cast<const ShallowCondition*> (element));
            };

            virtual void _accept(const UpperBoundsCondition *element) {
                _accept(static_cast<const ShallowCondition*> (element));
            };

            virtual void _accept(const LivenessCondition *element) {
                _accept(static_cast<const ShallowCondition*> (element));
            };

            virtual void _accept(const KSafeCondition *element) {
                _accept(static_cast<const ShallowCondition*> (element));
            };

            virtual void _accept(const QuasiLivenessCondition *element) {
                _accept(static_cast<const ShallowCondition*> (element));
            };

            virtual void _accept(const StableMarkingCondition *element) {
                _accept(static_cast<const ShallowCondition*> (element));
            };

            virtual void _accept(const BooleanCondition *element) {
                assert(false);
                std::cerr << "No accept for BooleanCondition" << std::endl;
                exit(0);
            };

            // Expression

            virtual void _accept(const UnfoldedIdentifierExpr *element) {
                assert(false);
                std::cerr << "No accept for UnfoldedIdentifierExpr" << std::endl;
                exit(0);
            };

            virtual void _accept(const LiteralExpr *element) {
                assert(false);
                std::cerr << "No accept for LiteralExpr" << std::endl;
                exit(0);
            };

            virtual void _accept(const PlusExpr *element) {
                _accept(static_cast<const CommutativeExpr*> (element));
            };

            virtual void _accept(const MultiplyExpr *element) {
                _accept(static_cast<const CommutativeExpr*> (element));
            };

            virtual void _accept(const MinusExpr *element) {
                assert(false);
                std::cerr << "No accept for MinusExpr" << std::endl;
                exit(0);
            };

            virtual void _accept(const NaryExpr *element) {
                assert(false);
                std::cerr << "No accept for LivenessCondition" << std::endl;
                exit(0);
            }

            virtual void _accept(const SubtractExpr *element) {
                _accept(static_cast<const NaryExpr*> (element));
            }

            // shallow expression, default to error

            virtual void _accept(const IdentifierExpr *element) {
                assert(false);
                std::cerr << "No accept for IdentifierExpr" << std::endl;
                exit(0);
            };
        };

        class ExpressionVisitor : public Visitor {
        public:

        private:

            void _accept(const NotCondition *element) override {
                assert(false);
                std::cerr << "No accept for NotCondition" << std::endl;
                exit(0);
            };

            void _accept(const AndCondition *element) override {
                assert(false);
                std::cerr << "No accept for AndCondition" << std::endl;
                exit(0);
            };

            void _accept(const OrCondition *element) override {
                assert(false);
                std::cerr << "No accept for OrCondition" << std::endl;
                exit(0);
            };

            void _accept(const LessThanCondition *element) override {
                assert(false);
                std::cerr << "No accept for LessThanCondition" << std::endl;
                exit(0);
            };

            void _accept(const LessThanOrEqualCondition *element) override {
                assert(false);
                std::cerr << "No accept for LessThanOrEqualCondition" << std::endl;
                exit(0);
            };

            void _accept(const EqualCondition *element) override {
                assert(false);
                std::cerr << "No accept for EqualCondition" << std::endl;
                exit(0);
            };

            void _accept(const NotEqualCondition *element) override {
                assert(false);
                std::cerr << "No accept for NotEqualCondition" << std::endl;
                exit(0);
            };

            void _accept(const DeadlockCondition *element) override {
                assert(false);
                std::cerr << "No accept for DeadlockCondition" << std::endl;
                exit(0);
            };

            void _accept(const CompareConjunction *element) override {
                assert(false);
                std::cerr << "No accept for CompareConjunction" << std::endl;
                exit(0);
            };

            void _accept(const UnfoldedUpperBoundsCondition *element) override {
                assert(false);
                std::cerr << "No accept for UnfoldedUpperBoundsCondition" << std::endl;
                exit(0);
            };
        };

        class BaseVisitor : public Visitor {
        protected:

            void _accept(const NotCondition *element) override {
                visit(this, element->getCond());
            }

            void _accept(const LogicalCondition *element) override {
                for (const auto &cond : *element) {
                    visit(this, cond);
                }
            }

            void _accept(const CompareCondition *element) override {
                visit(this, element->getExpr1());
                visit(this, element->getExpr2());
            }

            void _accept(const DeadlockCondition *element) override {
                // no-op
            }

            void _accept(const CompareConjunction *element) override {
                // no-op, complicated
            }

            void _accept(const UnfoldedUpperBoundsCondition *element) override {
                // no-op
            }

            void _accept(const SimpleQuantifierCondition *condition) override {
                visit(this, condition->getCond());
            }

            void _accept(const UntilCondition *condition) override {
                visit(this, (*condition)[0]);
                visit(this, (*condition)[1]);
            }

            void _accept(const ShallowCondition *element) override {
                if (const auto &compiled = element->getCompiled())
                    visit(this, compiled);
            }

            void _accept(const BooleanCondition *element) override {
                // no-op
            }

            void _accept(const UnfoldedIdentifierExpr *element) override {
                // no-op
            }

            void _accept(const LiteralExpr *element) override {
                // no-op
            }

            void _accept(const NaryExpr *element) override {
                for (const auto &expr : element->expressions()) {
                    visit(this, expr);
                }
            }

            void _accept(const MinusExpr *element) override {
                visit(this, (*element)[0]);
            }

            void _accept(const IdentifierExpr *element) override {
                if (const auto& compiled = element->compiled())
                    visit(this, compiled);
                // no-op
            }
        };

        // Used to make visitors that check if any node in the tree fulfills a condition

        class AnyVisitor : public BaseVisitor {
        public:
            [[nodiscard]] bool getReturnValue() const {
                return _condition_found;
            }

        protected:
            bool _condition_found = false;

            void setConditionFound() {
                _condition_found = true;
            }

        private:
        };
    }
}

#endif /* VISITOR_H */

